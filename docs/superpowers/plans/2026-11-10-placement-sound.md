# Placement Sound Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Play a short sound when a piece is successfully placed on the board.

**Architecture:** `main` owns one raylib `Sound`, loaded after audio initialization and unloaded before audio shutdown. Pass it to `gameplay_update`, which plays it only when `game_place_piece` returns a nonnegative result. Bundle a small generated WAV alongside the existing local background music.

**Tech Stack:** C11, raylib 5.5 audio API, standard-library WAV generation.

**Spec:** `docs/superpowers/specs/2026-11-10-placement-sound-design.md`

## Global Constraints

- Do not add a dependency or download an external audio file.
- Load `assets/audio/place.wav` once after `InitAudioDevice()`.
- Play only for `game_place_piece(...) >= 0`; invalid placements stay silent.
- A failed `LoadSound` logs an error and must not stop gameplay.
- Unload the sound before `CloseAudioDevice()`.

## Review Focus

- Accepted placement with zero cleared lines: still plays because result `0` is success (covered by existing `test_piece_offer`; verify by smoke test).
- Invalid/out-of-bounds placement: result `-1`, no sound (covered by existing game-placement tests; verify by smoke test).
- Missing/unreadable sound asset: invalid `Sound` is not played and gameplay continues (inspect validity guard and log path; runtime check when audio session permits).
- Shutdown: sound is unloaded while the audio device is still initialized (inspect cleanup order).
- Repeated updates: asset is loaded only at startup, not per input frame (inspect ownership/loading site).

---

### Task 1: Add placement feedback sound

**Files:**
- Create: `assets/audio/place.wav` — short ascending mono PCM effect, 16-bit, 22050 Hz, approximately 120 ms.
- Modify: `src/main.c` — load/check once after `InitAudioDevice`, pass the `Sound` to gameplay, and unload before closing audio.
- Modify: `src/screens/gameplay/gameplay.h`, `src/screens/gameplay/gameplay.c` — accept the `Sound` and play it only when placement returns `>= 0` and `IsSoundValid` is true.

**Interfaces:**
- Existing `int game_place_piece(Game *game, int offer_index, int row, int col)` returns `-1` for rejection and a nonnegative cleared-line count for success.
- New signature: `GameScreen gameplay_update(Game *game, Sound placement_sound)`.

- [x] **Step 1: Confirm placement-result contract before integration.** Run `cmake --build build --target test_piece_offer && ctest --test-dir build -R piece_offer --output-on-failure`. Expected: existing tests pass for accepted placements and rejected placements; no product code changed yet.
- [x] **Step 2: Add and verify the local WAV.** Generate the approximately 120 ms ascending pluck using Python's standard `wave`/`math` modules (one-off command, no committed generator); verify the file is mono 16-bit PCM at 22050 Hz and starts with a valid RIFF/WAVE header.
- [x] **Step 3: Integrate loading, playback, and cleanup.** Pass the loaded sound into `gameplay_update`; on release, call `PlaySound` only if `game_place_piece` returns `>= 0` and the sound is valid. Log load failure, keep playing without sound, and unload before `CloseAudioDevice`.
- [x] **Step 4: Verify build and behavior.** Run `cmake --build build` and `ctest --test-dir build --output-on-failure`; expected: build succeeds and all tests pass. If an audio-capable game session is available, confirm an accepted placement plays once and an invalid placement stays silent. Automated GUI interactions were attempted; raylib confirmed WAV loading, but playback count could not be independently confirmed in the mixed system-audio capture.
