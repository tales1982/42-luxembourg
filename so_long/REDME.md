# README - So_Long

Este é o projeto so_long desenvolvido como parte do currículo da 42. 
O objetivo deste jogo é criar um jogo de aventura simples utilizando a biblioteca gráfica MiniLibX.

## Índice
- Pré-requisitos
- Estrutura de Diretórios
- Compilação do Jogo
- Executando o Jogo
- Verificação de Vazamentos de Memória
- Estrutura do Arquivo so_long.h
- Considerações Finais

## Pré-requisitos
Certifique-se de ter as seguintes bibliotecas e ferramentas instaladas em seu sistema:
- MiniLibX: Biblioteca gráfica usada para desenhar a janela e imagens.
- Libft: Biblioteca de utilitários padrão.
- Valgrind (opcional): Ferramenta para detectar vazamentos de memória.

## Estrutura de Diretórios
O projeto possui a seguinte estrutura de diretórios:
so_long/
├── lib/
│   ├── libft/
│   └── minilibx-linux/
├── src/
│   ├── close_window.c
│   ├── draw_map.c
│   ├── key_event.c
│   ├── load_map.c
│   ├── start_game.c
│   └── copy_image_part.c
├── img/
│   ├── pacMan.xpm
│   ├── 0.xpm
│   └── 1.xpm
├── maps/
│   └── map.ber
├── so_long.c
├── so_long.h
└── Makefile

# Compilação do Jogo
- Clone o repositório:
- Copiar código
- git clone https://github.com/tales1982/42-luxembourg.git
- cd so_long
- Certifique-se de que as bibliotecas libft e minilibx-linux estão presentes:

## As bibliotecas libft e minilibx-linux devem estar nas pastas ./lib/libft e ./lib/minilibx-linux, respectivamente.

## Compile o jogo usando o Makefile:

# Copiar código
## make
- Este comando compilará o código-fonte, criando o executável so_long.

# Executando o Jogo
## Para executar o jogo, use o comando abaixo, passando o caminho para um arquivo de mapa .ber:

# Copiar código
- ./so_long maps/map.ber

## Nota: Certifique-se de que o arquivo de mapa está no formato correto.
- Verificação de Vazamentos de Memória
- Se desejar verificar vazamentos de memória usando Valgrind, utilize o comando:

## Copiar código
- make check
- Este comando executará o jogo dentro do Valgrind, verificando possíveis vazamentos de memória.

- Estrutura do Arquivo so_long.h
- O arquivo so_long.h define as estruturas de dados e funções utilizadas no jogo:

# Estruturas de Dados:

t_data: Contém todas as informações do jogo, incluindo a janela, mapa, imagens e posição do jogador.
t_image_data: Utilizada para manipulação de partes da imagem.
Funções Principais:

initialize_game_window: Inicializa a janela do jogo.
load_map: Carrega o mapa do arquivo especificado.
initialize_images: Carrega e inicializa as imagens necessárias.
start_game: Inicia o loop principal do jogo.
key_event: Trata eventos de teclado.
draw_map: Desenha o mapa na janela.
is_wall: Verifica se uma posição do mapa é uma parede.
update_position_and_image: Atualiza a posição do jogador e a imagem correspondente.
copy_image_part: Copia uma parte da imagem fonte para a imagem destino.
close_window: Fecha a janela do jogo.

## Considerações Finais
Este guia cobre os passos básicos para compilar e executar o jogo so_long. Certifique-se de seguir as instruções cuidadosamente para garantir que o jogo funcione corretamente. Se encontrar problemas, verifique se todas as dependências estão instaladas e se os caminhos dos arquivos estão corretos.
