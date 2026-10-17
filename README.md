# 🧩 Block Merge

**Block Merge** é um jogo de quebra-cabeça inspirado no popular *Block Blast*, no qual o objetivo é encaixar blocos em uma grade 8×8 para formar e eliminar linhas e colunas completas.

Combine estratégia e raciocínio lógico para aproveitar melhor o espaço disponível, acumular pontos e alcançar a maior pontuação possível. Simples de aprender, mas desafiador de dominar, Block Merge oferece uma experiência divertida para quem gosta de testar suas habilidades e superar seus próprios recordes.

> 🚧 **Status:** em desenvolvimento. Já existem o menu inicial e o desenho da grade 8×8.

## 🎯 Como jogar

1. A cada rodada, o jogo oferece **3 blocos** (peças) para você posicionar.
2. Arraste cada peça e encaixe na grade 8×8.
3. Sempre que uma **linha ou coluna ficar completa**, ela é eliminada e você ganha pontos.
4. Eliminar várias linhas/colunas de uma só vez gera **combos** com mais pontos.
5. **Fim de jogo:** se o jogador não conseguir encaixar um dos blocos oferecidos, ele perde.

## 🎮 Controles (planejado)

| Ação           | Tecla / Mouse           |
| -------------- | ----------------------- |
| Arrastar peça  | `A definir`             |
| Voltar ao menu | `A definir`             |
| Pausar         | `A definir`             |
| Reiniciar      | `A definir`             |

## ✅ Progresso

### Requisitos obrigatórios da disciplina (PIF 2026.2)

- [x] Linguagem C, em linha de comando
- [x] Biblioteca para jogos (raylib)
- [x] **Matrizes**: grade 8×8 representada por `int matriz[8][8]`
- [ ] **Estruturas (`struct`)**: peça, tabuleiro, estado do jogo
- [ ] **Ponteiros**: passagem de tabuleiro/peças por referência nas funções
- [ ] **Alocação dinâmica de memória**: `malloc`/`free` para peças e nós
- [ ] **Listas encadeadas**: ex.: fila de peças oferecidas e/ou ranking de pontuações
- [ ] **Leitura e escrita em arquivo**: salvar e carregar o top de pontuações
- [ ] **Animações e movimento**: arrastar peça, animação de limpeza de linhas
- [ ] **Tratamento de colisão**: peça × grade (encaixe válido) e peça × blocos ocupados
- [ ] Makefile / script / comando de compilação documentado

### Funcionalidades do jogo

- [x] Janela 800×800 com raylib
- [x] Menu principal com botão **Start**
- [x] Troca de tela (`MENU` → `JOGANDO`)
- [x] Desenho da grade 8×8 a partir da matriz
- [ ] Definição das peças (`piece.c`)
- [ ] Lógica do tabuleiro: encaixe e eliminação de linhas/colunas (`board.c`)
- [ ] Estados do jogo, pontuação e combos (`game.c`)
- [ ] Arrastar e soltar peças com o mouse
- [ ] Detecção de derrota (algum bloco não cabe) e tela de game over
- [ ] Tela "Como jogar"
- [ ] Sons e efeitos visuais

### Entregas

- [x] Parte 1: formulário com grupo, link do GitHub e descrição do jogo (13/10/2026)
- [ ] Vídeo curto do jogo rodando, com link no repositório
- [ ] Parte 2: entrega final com código-fonte e formulário (19/11/2026)
- [ ] Apresentação oral (24/11 ou 26/11)

## 🗂️ Estrutura do projeto

```
Block-Merge/
├── src/
│   ├── main.c        # Ponto de entrada, janela, menu e desenho da grade
│   ├── game.c        # Estado e loop do jogo
│   ├── board.c       # Lógica do tabuleiro
│   └── piece.c       # Definição e manipulação das peças
├── include/          # Headers (.h)
├── design.pen        # Protótipo visual do menu (1440×900)
├── CMakeLists.txt    # Configuração de build
└── README.md
```

## 🛠️ Tecnologias

- **Linguagem:** C (padrão C11)
- **Biblioteca gráfica:** [raylib](https://www.raylib.com/)
- **Build:** CMake ≥ 3.22
- **Compiladores:** GCC ou Clang

## 🚀 Como compilar e executar

### Pré-requisitos
- Compilador C (GCC ou Clang)
- CMake 3.22 ou superior
- raylib instalada e encontrável pelo CMake

```bash
# Ubuntu/Debian
sudo apt install build-essential cmake libraylib-dev

# macOS
brew install raylib cmake
```

### Build e execução

```bash
git clone <url-do-repositorio>
cd Jogo-PIF

cmake -S . -B build
cmake --build build

./build/BlockMerge
```

> No Windows, o executável fica em `build\BlockMerge.exe` (ou dentro de `build\Debug\` / `build\Release\`).

## 👤 Alunos

**Paulo César Regis de Lima** 

**Pedro Antonio Beltrão Rihan** 

**Ricardo Marinho do Prado** 
