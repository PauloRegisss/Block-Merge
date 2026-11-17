# 🧩 Block Merge

**Block Merge** é um jogo de quebra-cabeça inspirado no popular *Block Blast*, no qual o objetivo é encaixar blocos em uma grade 8×8 para formar e eliminar linhas e colunas completas.

Combine estratégia e raciocínio lógico para aproveitar melhor o espaço disponível, acumular pontos e alcançar a maior pontuação possível. Simples de aprender, mas desafiador de dominar, Block Merge oferece uma experiência divertida para quem gosta de testar suas habilidades e superar seus próprios recordes.

> ✅ **Status:** jogo completo e jogável: menu, partida, game over, recorde salvo em arquivo, música e efeito sonoro.

## 🎯 Como jogar

1. A cada rodada, o jogo oferece **3 peças** na bandeja abaixo do tabuleiro.
2. Arraste cada peça com o mouse e solte na grade 8×8. Uma prévia mostra onde ela vai cair.
3. Sempre que uma **linha ou coluna ficar completa**, ela é eliminada.
4. Cada peça encaixada soma pontos de acordo com a quantidade de blocos dela.
5. Quando as 3 peças são usadas, uma nova rodada é oferecida (sempre possível de encaixar).
6. **Fim de jogo:** se as peças restantes não couberem mais em nenhum lugar da grade, o jogador perde.

Seu recorde fica salvo em `highscores.txt` e aparece no menu e durante a partida.

## 🎮 Controles

| Ação                    | Tecla / Mouse         |
| ----------------------- | --------------------- |
| Arrastar e soltar peça  | `Botão esq do mouse`  |
| Jogar novamente (game over) | `R` ou botão na tela |
| Voltar ao menu (game over)  | Botão na tela     |

## ✅ Progresso

### Requisitos obrigatórios da disciplina (PIF 2026.2)

- [x] Linguagem C, em linha de comando
- [x] Biblioteca para jogos (raylib)
- [x] **Matrizes**: tabuleiro 8×8 (`int cells[8][8]`) e formato das peças (`int shape[3][3]`)
- [x] **Estruturas (`struct`)**: `Piece`, `PieceOffer`, `Board`, `Game`, `ScoreList`
- [x] **Ponteiros**: tabuleiro, peças e jogo passados por referência nas funções
- [x] **Alocação dinâmica de memória**: `realloc`/`free` na lista de pontuações (`ScoreList`)
- [x] **Listas encadeadas**: a lista de pontuações usa array dinâmico, não nós encadeados
- [x] **Leitura e escrita em arquivo**: `highscores.txt` carregado ao iniciar e salvo ao fim de cada partida
- [x] **Animações e movimento**: arrastar peça com prévia de encaixe
- [x] **Tratamento de colisão**: peça × grade (limites) e peça × blocos ocupados
- [x] Makefile / script / comando de compilação documentado (Linux, macOS e Windows)

### Funcionalidades do jogo

- [x] Janela redimensionável, ajustada ao tamanho do monitor
- [x] Menu principal com botão **Jogar**
- [x] Troca de telas (`MENU` → `JOGANDO` → `GAME OVER`)
- [x] Desenho da grade 8×8 a partir da matriz
- [x] 15 formatos de peças com cores da paleta (`piece.c`)
- [x] Lógica do tabuleiro: encaixe e eliminação de linhas/colunas (`board.c`)
- [x] Estado do jogo, pontuação e geração de peças sempre jogáveis (`game.c`)
- [x] Arrastar e soltar peças com o mouse
- [x] Detecção de derrota e tela de game over
- [x] Recorde local persistente (`highscore.c`)
- [x] Música de fundo e som ao encaixar uma peça
- [x] Testes automatizados (CTest) para peças, ofertas/regras do jogo e recorde

### Entregas

- [x] Parte 1: formulário com grupo, link do GitHub e descrição do jogo (13/10/2026)
- [ ] Vídeo curto do jogo rodando, com link no repositório
- [ ] Parte 2: entrega final com código-fonte e formulário (19/11/2026)
- [ ] Apresentação oral (24/11 ou 26/11)

## 🗂️ Estrutura do projeto

```
Block-Merge/
├── src/
│   ├── main.c                # Janela, áudio, loop principal e troca de telas
│   ├── game/
│   │   ├── board.c / .h      # Lógica do tabuleiro
│   │   ├── game.c / .h       # Estado do jogo, pontuação e oferta de peças
│   │   └── highscore.c / .h  # Lista de pontuações (carregar/salvar)
│   ├── materials/
│   │   └── piece.c / .h      # Formatos, cores e desenho das peças
│   └── screens/
│       ├── screen.h          # Enum das telas
│       ├── fonts/            # Carregamento das fontes (Anton e Geist)
│       ├── menu/             # Tela de menu
│       ├── gameplay/         # Tela da partida (arrastar e soltar)
│       └── gameover/         # Tela de fim de jogo
├── tests/                    # Testes CTest (peças, ofertas, recorde)
├── assets/                   # Fontes e áudio (place.wav, musica_fundo.wav)
├── docs/superpowers/         # Specs e planos das funcionalidades
├── highscores.txt            # Recorde local (gerado ao jogar)
├── design.pen                # Protótipo visual do menu (1440×900)
├── CMakeLists.txt            # Configuração de build
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
git clone <url-do-repositorio>
cd Jogo-PIF
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

> ⚠️ Execute o jogo a partir da **raiz do repositório**: as pastas `assets/` e o arquivo `highscores.txt` são lidos por caminho relativo.

> Se a configuração falhar com erro de gerador (por exemplo, `nmake`), apague a pasta `build` (`rmdir /s /q build` no CMD ou `rm -rf build` no MSYS2) e rode o `cmake -S . -B build -G Ninja` de novo.

### Testes

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## 👤 Alunos

**Paulo César Régis de Lima**

**Pedro Antonio Beltrão Rihan**

**Ricardo Marinho do Prado**
