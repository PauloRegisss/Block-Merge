# 🧩 Block Merge

**Block Merge** é um jogo de quebra-cabeça inspirado no popular *Block Blast*. O objetivo é encaixar blocos em uma grade 8×8 para formar e eliminar linhas e colunas completas.

Combine estratégia e raciocínio lógico para aproveitar melhor o espaço disponível, acumular pontos e alcançar a maior pontuação possível. Simples de aprender, mas desafiador de dominar, o Block Merge é uma ótima forma de testar suas habilidades e superar seus próprios recordes.

> ✅ **Status:** jogo completo e jogável, com menu, partida, game over, recorde salvo em arquivo, música e efeito sonoro.

## 🎯 Como jogar

1. A cada rodada, o jogo oferece **3 peças** na bandeja abaixo do tabuleiro.
2. Arraste cada peça com o mouse e solte na grade 8×8. Uma prévia mostra onde ela vai cair.
3. Sempre que uma **linha ou coluna ficar completa**, ela é eliminada.
4. Cada peça encaixada soma pontos de acordo com a quantidade de blocos dela.
5. Quando as 3 peças são usadas, uma nova rodada é oferecida (sempre possível de encaixar).
6. **Fim de jogo:** se as peças restantes não couberem em nenhum lugar da grade, o jogador perde.

O recorde fica salvo em `highscores.txt` e aparece no menu e durante a partida.

## 🎮 Controles

| Ação                        | Controle                  |
| --------------------------- | ------------------------- |
| Arrastar e soltar peça      | Botão esquerdo do mouse   |
| Jogar novamente (game over) | Botão na tela             |
| Voltar ao menu (game over)  | Botão na tela             |

## ✅ Progresso

### Requisitos obrigatórios da disciplina (PIF 2026.2)

- [x] Linguagem C
- [x] Biblioteca para jogos (raylib)
- [x] **Matrizes**: tabuleiro 8×8 (`int cells[8][8]`) e formato das peças (`int shape[3][3]`)
- [x] **Estruturas (`struct`)**: `Piece`, `PieceOffer`, `Board`, `Game`, `ScoreNode`, `ScoreList`
- [x] **Ponteiros**: tabuleiro, peças e jogo passados por referência nas funções
- [x] **Alocação dinâmica de memória**: `malloc`/`free` dos nós da lista de pontuações
- [x] **Listas encadeadas**: a lista de pontuações (`ScoreList`) usa nós encadeados (`ScoreNode`), ordenada da maior para a menor pontuação
- [x] **Leitura e escrita em arquivo**: `highscores.txt` é carregado ao iniciar e salvo ao fim de cada partida
- [x] **Animações e movimento**: arrastar a peça com prévia de encaixe
- [x] **Tratamento de colisão**: peça × limites da grade e peça × blocos ocupados
- [x] Comando de compilação documentado com CMake (Linux, macOS e Windows)

### Funcionalidades do jogo

- [x] Janela redimensionável, ajustada ao tamanho do monitor
- [x] Menu principal com botão **Jogar**
- [x] Troca de telas (`MENU` → `JOGANDO` → `GAME OVER`)
- [x] Desenho da grade 8×8 a partir da matriz
- [x] 15 formatos de peças com cores da paleta (`piece.c`)
- [x] Lógica do tabuleiro: encaixe e eliminação de linhas e colunas (`board.c`)
- [x] Estado do jogo, pontuação e geração de peças sempre jogáveis (`game.c`)
- [x] Arrastar e soltar peças com o mouse
- [x] Detecção de derrota e tela de game over
- [x] Recorde local persistente (`highscore.c`)
- [x] Música de fundo e som ao encaixar uma peça
- [x] Testes automatizados (CTest) para peças, ofertas/regras do jogo e recorde

### Entregas

- [x] Parte 1: formulário com grupo, link do GitHub e descrição do jogo (13/10/2026)
- [x] Vídeo curto do jogo rodando: [Assistir no YouTube](https://youtu.be/k5wsZRyCmTk)

## 🗂️ Estrutura do projeto

Todos os headers (`.h`) ficam na pasta `include/`, e os arquivos de implementação (`.c`) ficam em `src/`.

```
Block-Merge/
├── include/                      # Todos os headers (.h) do projeto
│   ├── board.h                   # Lógica do tabuleiro
│   ├── game.h                    # Estado do jogo, pontuação e oferta de peças
│   ├── highscore.h               # Lista encadeada de pontuações (carregar/salvar)
│   ├── piece.h                   # Formatos, cores e desenho das peças
│   ├── screen.h                  # Enum das telas
│   ├── fonts.h                   # Carregamento das fontes (Anton e Geist)
│   ├── menu.h                    # Tela de menu
│   ├── gameplay.h                # Tela da partida (arrastar e soltar)
│   └── gameover.h                # Tela de fim de jogo
├── src/
│   ├── main.c                    # Janela, áudio, loop principal e troca de telas
│   ├── game/
│   │   ├── board.c
│   │   ├── game.c
│   │   └── highscore.c
│   ├── materials/
│   │   └── piece.c
│   └── screens/
│       ├── fonts/fonts.c
│       ├── menu/menu.c
│       ├── gameplay/gameplay.c
│       └── gameover/gameover.c
├── tests/                        # Testes CTest (peças, ofertas, recorde)
├── assets/                       # Fontes e áudio (place.wav, musica_fundo.wav)
├── docs/superpowers/             # Specs e planos das funcionalidades
├── highscores.txt                # Recorde local (gerado ao jogar)
├── design.pen                    # Protótipo visual do menu (1440×900)
├── CMakeLists.txt                # Configuração de build
└── README.md
```

## 🛠️ Tecnologias

- **Linguagem:** C (padrão C11)
- **Biblioteca gráfica e de áudio:** [raylib](https://www.raylib.com/) 5.5
- **Build:** CMake ≥ 3.22
- **Compiladores:** GCC ou Clang

## 🚀 Como compilar e executar

### Pré-requisitos

- Compilador C (GCC ou Clang)
- CMake 3.22 ou superior
- raylib 5.5 (se não for encontrada, o CMake baixa automaticamente)

**Ubuntu/Debian**

```bash
sudo apt install build-essential cmake libraylib-dev
```

**macOS**

```bash
brew install raylib cmake
```

**Windows (MSYS2)**

1. Instale o [MSYS2](https://www.msys2.org).
2. Abra o terminal **MSYS2 UCRT64** e rode:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-raylib
```

3. Rode os comandos de build pelo próprio terminal **MSYS2 UCRT64**, ou adicione `C:\msys64\ucrt64\bin` ao PATH do Windows e reabra o terminal.

Confira a instalação com `gcc --version` e `cmake --version`.

### Build e execução

```bash
git clone https://github.com/PauloRegisss/Block-Merge.git
cd Block-Merge
```

**Linux / macOS**

```bash
cmake -S . -B build
cmake --build build
./build/BlockMerge
```

**Windows (MSYS2)**

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/BlockMerge.exe
```

> ⚠️ Execute o jogo a partir da **raiz do repositório**: a pasta `assets/` e o arquivo `highscores.txt` são lidos por caminho relativo.

> Se a configuração falhar com erro de gerador (por exemplo, `nmake`), apague a pasta `build` (`rmdir /s /q build` no CMD ou `rm -rf build` no MSYS2) e rode `cmake -S . -B build -G Ninja` de novo.

### Testes

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## 👤 Alunos

- **Paulo César Régis de Lima**
- **Pedro Antonio Beltrão Rihan**
- **Ricardo Marinho do Prado**
