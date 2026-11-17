# High score local — design

- **Intent:** preservar o recorde do jogador entre execuções e deixá-lo visível no menu e durante a partida.
- **Abordagens:** criar um arquivo novo exclusivo para o recorde ou conectar `src/game/highscore.c`, que já mantém uma lista local de pontuações ordenada. Escolha: reutilizar o módulo existente para evitar duplicação.
- **Comportamento:** carregar a lista ao iniciar; ao sair da partida por game over, adicionar a pontuação e salvar; mostrar `scores_best` no menu e na tela de jogo. Uma primeira execução sem arquivo começa com recorde zero.
- **Persistência:** arquivo de texto `highscores.txt` no diretório de trabalho, compatível com os comandos de execução documentados no README.
- **Fora de escopo:** sincronização entre dispositivos, ranking online, edição/reset do recorde e implementação completa da tela de game over.
- **Verificação:** teste automatizado de carregar/salvar/adicionar pontuações e execução da suíte/build existentes.
