# "Philosophers"

O exercício "Philosophers" da Escola 42 é um clássico problema da computação conhecido 
como o "Problema dos Filósofos Comensais". Esse problema envolve questões de sincronização
e concorrência, onde você terá que lidar com threads e a coordenação entre elas 
para evitar problemas como deadlocks e race conditions.

Aqui está uma lista de tópicos que você deve estudar para ter uma boa base para resolver o exercício:

- 1. Threads em C
Criação e manipulação de threads: Entenda como criar, 
iniciar e terminar threads usando a biblioteca pthread em C.
pthread_create, pthread_join: Estude como essas funções são usadas para gerenciar threads.
Passagem de parâmetros para threads: Aprenda como passar parâmetros para funções executadas por threads.
- 2. Sincronização
Mutexes (pthread_mutex_t): Fundamental para evitar race conditions, 
permitindo que apenas uma thread acesse um recurso compartilhado por vez.
Condicionais (pthread_cond_t): Úteis para fazer com que threads esperem 
por uma condição específica antes de continuar a execução.
Semáforos (sem_t): Para controlar o acesso a recursos limitados.
- 3. Problemas de Concorrência
Race conditions: Entenda o que são e como evitá-los usando mutexes e outras técnicas de sincronização.
Deadlocks: Compreenda como eles ocorrem e como podem ser evitados (ex.: ordenação dos mutexes, timeouts).
Starvation: Aprenda sobre a situação onde uma thread nunca consegue acessar um recurso necessário.
- 4. O Problema dos Filósofos Comensais
Entendimento do problema: Os filósofos estão sentados em volta de uma mesa com garfos entre eles. 
Eles devem pensar e comer, mas só podem comer se conseguirem pegar os dois garfos adjacentes.
Soluções clássicas: Estude diferentes abordagens para resolver o problema, como a solução de Dijkstra e a solução com semáforos.
- 5. Programação Paralela e Concorrente
Modelos de concorrência: Entenda as diferentes abordagens para programação concorrente,
como threads, processos, e programação assíncrona.
Detecção e resolução de deadlocks: Ferramentas e técnicas para identificar
e corrigir deadlocks em sistemas concorrentes.
- 6. Exemplos e Prática
Exemplos de código: Estude exemplos práticos de implementação de threads e sincronização em C.
Implementação de soluções para problemas clássicos de sincronização: Como o problema 
do produtor-consumidor, leitores-escritores, etc.
- 7. Leitura e Discussão
Documentação da biblioteca pthread: Familiarize-se com a documentação oficial da biblioteca,
que será sua principal ferramenta.
Artigos e livros sobre concorrência: Recursos como "Operating Systems: Three Easy Pieces" e "The Little Book of Semaphores" podem ser úteis.
- 8. Testes e Debugging
Valgrind e outros depuradores: Use ferramentas como Valgrind para detectar
 problemas como leaks de memória e race conditions.
Testes de estresse: Crie testes que estressem seu código para garantir que ele não falhe em condições de alta concorrência.
- 9. Desenvolvimento de Pensamento Algorítmico
Dividir o problema: Pratique a divisão do problema em partes menores e mais manejáveis, 
abordando cada parte individualmente antes de integrá-las.