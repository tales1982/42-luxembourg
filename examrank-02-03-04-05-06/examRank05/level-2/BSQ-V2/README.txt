=== BSQ (Biggest Square) ===

COMPILAÇÃO:
  cc -std=c99 -Wall -Wextra -Werror *.c -o programa

ARQUIVOS:
  - bsq.h           : Headers e estruturas de dados
  - map_reader.c    : Leitura e validação do mapa
  - solver.c        : Algoritmo para encontrar o maior quadrado
  - output.c        : Funções de saída
  - main.c          : Função principal

USO:
  ./programa <arquivo>    # Ler de arquivo
  ./programa              # Ler de stdin
  cat mapa | ./programa   # Ler de stdin via pipe

FORMATO DO ARQUIVO:
  Primeira linha: [número_de_linhas][char_vazio][char_obstáculo][char_preencher]
  Exemplo: 9.ox
    - 9 linhas
    - '.' = espaço vazio
    - 'o' = obstáculo  
    - 'x' = preenchimento

  Linhas seguintes: mapa com apenas chars vazios e obstáculos
  - Todas as linhas devem ter o mesmo comprimento
  - Cada linha termina com '\n'
  - Apenas caracteres imprimíveis (ASCII 32-126)
  - Os 3 caracteres (vazio, obstáculo, preencher) devem ser diferentes

TESTES:
  ./run_tests.sh          # Executa todos os testes
  
  Casos de teste inclusos:
  - test1.stdin : Mapa 5x5 vazio (quadrado 5x5)
  - test2.stdin : Mapa 3x3 com obstáculo central (quadrado 2x2)
  - test3.stdin : Mapa 1x1 com obstáculo (sem quadrado)
  - test4.stdin : Mapa 1x1 vazio (quadrado 1x1)
  - test5.stdin : Exemplo do subject (quadrado 7x7)
  - test6.stdin : Mapa com espaços e números (quadrado 2x2)
  
  Testes de erro:
  - test_error1.stdin : Linhas de tamanhos diferentes
  - test_error2.stdin : Caracteres duplicados no header
  - test_error3.stdin : Caractere inválido no mapa

ALGORITMO:
  Usa programação dinâmica (Dynamic Programming) para encontrar
  o maior quadrado em O(rows × cols).
  
  Em caso de empate, escolhe o quadrado mais próximo:
  1. Do topo (menor linha)
  2. Da esquerda (menor coluna)

FUNÇÕES PERMITIDAS:
  malloc, calloc, realloc, free, fopen, fclose, getline, 
  fscanf, fputs, fprintf, fputc, stdout, stdin
