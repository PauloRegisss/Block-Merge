# Placement sound — design

- **Intent:** give the player immediate audio feedback when a piece is successfully placed.
- **Approaches:** synthesize a sound at runtime (more audio code), fetch an external effect (source/licensing/dependency), or ship a short WAV. Choice: a small local WAV, matching the existing local music asset pattern.
- **Behavior:** load `assets/audio/place.wav` once after `InitAudioDevice`; play it only when `game_place_piece()` accepts a placement (`result >= 0`); invalid placements remain silent. If loading fails, log an error and keep gameplay running without the effect.
- **Implementation:** main owns and unloads the raylib `Sound`; pass it to `gameplay_update` rather than coupling sound playback to game rules. Generate a short, gentle ascending pluck as a self-contained mono WAV, with no external dependency.
- **Non-goals:** sound settings/muting UI, changing background music, sounds for line clears or invalid moves, external downloads.
- **Verification:** build and run the existing CTest suite; smoke-test a successful placement and an invalid placement when an audio-capable game session is available.
