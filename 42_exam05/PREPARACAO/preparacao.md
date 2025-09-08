📑 Lista de Exercícios para Treinar o BSQ

🔹 Etapa 1 — Leitura de dados



Ler uma linha do stdin com getline e imprimir no ecrã.

👉 Treina getline.

🔹 Etapa 1 — Leitura de dados

Ler uma linha do stdin com getline e imprimir no ecrã.

👉 Treina getline.

Abrir um ficheiro com fopen e ler todas as linhas até EOF.

👉 Treina fopen, fclose.

Contar o número de linhas num ficheiro.

👉 Treina laços (while (getline...)).

🔹 Etapa 2 — Manipulação de strings

Remover o \n do fim da string lida por getline.

👉 Treina índices e strlen.

Verificar se todas as linhas de um ficheiro têm o mesmo comprimento.

👉 É o início da validação do mapa.

Verificar se uma linha só contém caracteres de um conjunto válido

(por exemplo, apenas . e o).

👉 Treina loops e comparação de caracteres.

🔹 Etapa 3 — Memória dinâmica

Guardar todas as linhas de um ficheiro em um array de strings usando malloc/calloc.

👉 Treina arrays 2D.

Libertar corretamente toda a memória com free.

👉 Previne memory leaks.

🔹 Etapa 4 — Representação do mapa

Criar uma struct Map com:

número de linhas (h),

número de colunas (w),

char empty, char obstacle, char full,

char **lines.

👉 Já começa a parecer com o BSQ.

Ler o cabeçalho (n empty obstacle full) com fscanf.

👉 Treina parsing.

Validar se os 3 caracteres são distintos.

👉 Parte da regra de mapa válido.

🔹 Etapa 5 — Algoritmo do maior quadrado (DP)

Criar um array dp igual ao mapa mas só com 0 e 1

(1 = célula vazia, 0 = obstáculo).

👉 Treina conversão de dados.

Implementar a fórmula do DP para calcular o maior quadrado.

👉 Esse é o coração do exercício.

Testar o DP num mapa pequeno e imprimir o tamanho do maior quadrado.

👉 Verifica se funciona.

Tratar empates: se houver mais de um quadrado do mesmo tamanho, escolher o mais alto → mais à esquerda.

👉 Aplica a regra do enunciado.

🔹 Etapa 6 — Saída do programa

Substituir as células do maior quadrado por full no lines.

👉 Treina manipulação do mapa original.

Imprimir o mapa resultante no stdout.

👉 Treina fputs e loops.

Tratar erros: se o mapa for inválido, imprimir "map error\n" no stderr.

👉 Treina fprintf(stderr, ...).

🔹 Etapa 7 — Integração

Ler um mapa de stdin e resolver.

👉 cat mapa.txt | ./bsq.

Resolver múltiplos mapas (argumentos)

👉 ./bsq mapa1 mapa2 mapa3.

Garantir quebra de linha entre as saídas.

👉 Detalhe importante para passar nos testes.

🔹 Etapa 8 — Testes extras

Testar mapa válido simples (sem obstáculos).

Testar mapa com apenas obstáculos.

Testar mapa inválido (linhas de tamanhos diferentes).

Testar mapa vazio (0 linhas → deve dar erro).



Abrir um ficheiro com fopen e ler todas as linhas até EOF.

👉 Treina fopen, fclose.



Contar o número de linhas num ficheiro.

👉 Treina laços (while (getline...)).



🔹 Etapa 2 — Manipulação de strings



Remover o \n do fim da string lida por getline.

👉 Treina índices e strlen.



Verificar se todas as linhas de um ficheiro têm o mesmo comprimento.

👉 É o início da validação do mapa.



Verificar se uma linha só contém caracteres de um conjunto válido

(por exemplo, apenas . e o).

👉 Treina loops e comparação de caracteres.



🔹 Etapa 3 — Memória dinâmica



Guardar todas as linhas de um ficheiro em um array de strings usando malloc/calloc.

👉 Treina arrays 2D.



Libertar corretamente toda a memória com free.

👉 Previne memory leaks.



🔹 Etapa 4 — Representação do mapa



Criar uma struct Map com:



número de linhas (h),



número de colunas (w),



char empty, char obstacle, char full,



char **lines.

👉 Já começa a parecer com o BSQ.



Ler o cabeçalho (n empty obstacle full) com fscanf.

👉 Treina parsing.



Validar se os 3 caracteres são distintos.

👉 Parte da regra de mapa válido.



🔹 Etapa 5 — Algoritmo do maior quadrado (DP)



Criar um array dp igual ao mapa mas só com 0 e 1

(1 = célula vazia, 0 = obstáculo).

👉 Treina conversão de dados.



Implementar a fórmula do DP para calcular o maior quadrado.

👉 Esse é o coração do exercício.



Testar o DP num mapa pequeno e imprimir o tamanho do maior quadrado.

👉 Verifica se funciona.



Tratar empates: se houver mais de um quadrado do mesmo tamanho, escolher o mais alto → mais à esquerda.

👉 Aplica a regra do enunciado.



🔹 Etapa 6 — Saída do programa



Substituir as células do maior quadrado por full no lines.

👉 Treina manipulação do mapa original.



Imprimir o mapa resultante no stdout.

👉 Treina fputs e loops.



Tratar erros: se o mapa for inválido, imprimir "map error\n" no stderr.

👉 Treina fprintf(stderr, ...).



🔹 Etapa 7 — Integração



Ler um mapa de stdin e resolver.

👉 cat mapa.txt | ./bsq.



Resolver múltiplos mapas (argumentos)

👉 ./bsq mapa1 mapa2 mapa3.



Garantir quebra de linha entre as saídas.

👉 Detalhe importante para passar nos testes.



🔹 Etapa 8 — Testes extras



Testar mapa válido simples (sem obstáculos).



Testar mapa com apenas obstáculos.



Testar mapa inválido (linhas de tamanhos diferentes).



Testar mapa vazio (0 linhas → deve dar erro).
