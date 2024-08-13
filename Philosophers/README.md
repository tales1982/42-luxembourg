# Simulação do Problema dos Filósofos

## Descrição do Problema

O problema dos filósofos trata de uma situação onde cinco filósofos estão sentados em torno de uma mesa redonda. 
Cada filósofo pode alternadamente pensar, comer ou ficar faminto. Para comer, um filósofo precisa usar dois garfos, 
um à sua esquerda e outro à sua direita. No entanto, existe apenas um garfo entre cada par de filósofos adjacentes, 
o que pode levar a situações de deadlock, onde todos os filósofos estão esperando indefinidamente pelos garfos.

## Estrutura do Projeto

O projeto está dividido em vários arquivos de código-fonte:

- **philo.c**: Contém a função `main` que inicializa a simulação.
- **launch.c**: Implementa a lógica principal da simulação, incluindo a criação e gerenciamento das threads dos filósofos.
- **msg_error.c**: Contém a função `handle_error`, que lida com a exibição das mensagens de erro.
- **start.c**: Implementa as funções de inicialização, como a configuração dos mutexes e a criação das estruturas dos filósofos.
- **utils.c**: Contém funções utilitárias, como a obtenção do tempo atual e a simulação de dormir dos filósofos.
- **philo.h**: Arquivo de cabeçalho que declara as estruturas e funções utilizadas em todo o projeto.

## Funcionamento do Código

### Estruturas Principais

- **t_philosopher**: Estrutura que representa cada filósofo. Contém informações como seu ID, o número de refeições que ele já fez,
e os IDs dos garfos à sua esquerda e direita.
- **t_simulation**: Estrutura que contém as regras da simulação, como o número de filósofos, tempos de morte, comer, dormir, 
e mutexes para sincronização das threads.

### Fluxo de Execução

1. **Inicialização**:
   - A função `init_simulation` configura os parâmetros da simulação a partir dos argumentos passados pela linha de comando e inicializa os mutexes e as estruturas dos filósofos.

2. **Execução da Simulação**:
   - A função `launch_simulation` cria uma thread para cada filósofo. Cada thread executa a função `philo_thread`, que controla o ciclo de vida do filósofo (comer, dormir e pensar).
   - A função `philo_dines` gerencia o processo de um filósofo pegar os garfos, comer e liberar os garfos.

3. **Verificação de Condições de Parada**:
   - A função `check_death` monitora a simulação para verificar se algum filósofo morreu ou se todos os filósofos já comeram o número de vezes necessário.
   - Se algum filósofo morrer ou todos tiverem comido o suficiente, a simulação é interrompida.

4. **Limpeza**:
   - A função `cleanup_simulation` é chamada para garantir que todas as threads sejam corretamente finalizadas e que os mutexes sejam destruídos.

### Mensagens de Erro

- **handle_error**: Esta função exibe mensagens de erro específicas para diferentes problemas encontrados durante a simulação, como argumentos inválidos ou falhas na inicialização de mutexes ou criação de threads.

## Execução

### Compilação

Para compilar o projeto, utilize o comando `make` no terminal:

```bash
make
```
# Execução do Programa
- Após a compilação, execute o programa com o seguinte formato de comando:

´´´ bash

./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
´´´
- **num_philos**: Número de filósofos (e garfos).
- **time_to_die**: Tempo máximo (em milissegundos) que um filósofo pode ficar sem comer antes de morrer.
- **time_to_eat**: Tempo que um filósofo leva para comer (em milissegundos).
- **time_to_sleep**: Tempo que um filósofo passa dormindo (em milissegundos).
- **meals_required (opcional)**: Número de vezes que cada filósofo deve comer antes que a simulação termine.
## Exemplo de execução:

```bash
./philo 5 800 200 200 3
```