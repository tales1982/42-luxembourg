# Simulação do Problema dos Filósofos
## Descrição do Problema
O problema dos filósofos trata de uma situação onde vários filósofos estão sentados em torno de uma mesa redonda. Cada filósofo pode alternadamente pensar, comer ou ficar faminto. Para comer, um filósofo precisa usar dois garfos, um à sua esquerda e outro à sua direita. No entanto, existe apenas um garfo entre cada par de filósofos adjacentes, o que pode levar a situações de deadlock, onde todos os filósofos estão esperando indefinidamente pelos garfos.

## Estrutura do Projeto
O projeto está dividido em vários arquivos de código-fonte:

- **philo.c**: Contém a função philo_dines que gerencia a ação de jantar dos filósofos e a função philo_thread, que executa o ciclo de vida de cada filósofo.
- **launch.c**: Implementa a lógica principal da simulação, incluindo a criação e gerenciamento das threads dos filósofos e a verificação das condições de morte ou conclusão da simulação.
- **msg_error.c**: Contém a função handle_error, que lida com a exibição das mensagens de erro.
- **start.c**: Implementa as funções de inicialização, como a configuração dos mutexes e a criação das estruturas dos filósofos.
- **utils.c**: Contém funções utilitárias como a conversão de string para inteiro (ft_atoi), a obtenção do tempo atual e o cálculo de diferenças de tempo.
- **philo_utils.c**: Contém funções para logar as ações dos filósofos, calcular diferenças de tempo, fazer os filósofos dormirem e marcar o final da simulação.
- **philo_actions.c**: Implementa as ações principais dos filósofos, como comer (philo_eats) e dormir/pensar (philo_sleeps_and_thinks).
- **simulation.c**: Gerencia a inicialização, verificação de morte, verificação se todos os filósofos comeram o suficiente, e o encerramento da simulação.
- **philo.h**: Arquivo de cabeçalho que declara as estruturas e funções utilizadas em todo o projeto.
##Funcionamento do Código
### Estruturas Principais
- **t_philosopher**: Estrutura que representa cada filósofo. Contém informações como seu ID, o número de refeições que ele já fez, e os IDs dos garfos à sua esquerda e direita.
- **t_simulation**: Estrutura que contém as regras da simulação, como o número de filósofos, tempos de morte, comer, dormir, e mutexes para sincronização das threads.
### Fluxo de Execução

1. - A função init_simulation configura os parâmetros da simulação a partir dos argumentos passados pela linha de comando e inicializa os mutexes e as estruturas dos filósofos.
2. - A função init_mutexes é responsável por criar os mutexes necessários para os garfos, controle de refeições e a escrita no console.
3. - A função setup_philos prepara as estruturas dos filósofos, associando cada um aos seus respectivos garfos.
Execução da Simulação:

4. - A função launch_simulation cria uma thread para cada filósofo. Cada thread executa a função philo_thread, que controla o ciclo de vida do filósofo (comer, dormir e pensar).
5. - A função philo_dines gerencia o processo de um filósofo pegar os garfos, comer e liberar os garfos. Se houver apenas um filósofo, ele pegará um garfo e morrerá após o tempo especificado (time_to_die).
As ações de comer e dormir/pensar são implementadas nas funções philo_eats e philo_sleeps_and_thinks em philo_actions.c.
Verificação de Condições de Parada:

6. - A função check_death_and_full monitora a simulação para verificar se algum filósofo morreu ou se todos os filósofos já comeram o número de vezes necessário.
Se algum filósofo morrer ou todos tiverem comido o suficiente, a simulação é interrompida.
Limpeza:

8. - A função cleanup_simulation é chamada para garantir que todas as threads sejam corretamente finalizadas e que os mutexes sejam destruídos.
Mensagens de Erro
9. - handle_error: Esta função exibe mensagens de erro específicas para diferentes problemas encontrados durante a simulação, como argumentos inválidos ou falhas na inicialização de mutexes ou criação de threads.
## Execução
###Compilação
Para compilar o projeto, utilize o comando make no terminal:

```bash
make
```

## Execução do Programa
- Após a compilação, execute o programa com o seguinte formato de comando:

```bash
./philo <num_philos> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
```
- **num_philos**: Número de filósofos (e garfos).
- **time_to_die**: Tempo máximo (em milissegundos) que um filósofo pode ficar sem comer antes de morrer.
- **time_to_eat**: Tempo que um filósofo leva para comer (em milissegundos).
- **time_to_sleep**: Tempo que um filósofo passa dormindo (em milissegundos).
- **meals_required** (opcional): Número de vezes que cada filósofo deve comer antes que a simulação termine.
Exemplo de Execução:
```bash
./philo 5 800 200 200 3
```
- Neste exemplo, o programa simula 5 filósofos, onde cada filósofo tem 800ms antes de morrer de fome, leva 200ms para comer, 200ms para dormir e precisa comer 3 vezes antes de terminar a simulação.

## Funções Implementadas

### Arquivo philo.c

- philo_dines:
- Implementa a lógica de um filósofo durante o jantar. Ele tenta pegar os dois garfos para comer, atualiza o tempo da última refeição, e libera os garfos após terminar de comer.

- **philo_thread**:
- Representa a rotina da thread de cada filósofo. Cada filósofo alterna entre comer, dormir e pensar, verificando constantemente se outro filósofo morreu ou se todos já comeram o suficiente.

### Arquivo launch.c

- **launch_simulation**:
- Inicia a simulação criando as threads para cada filósofo e monitorando as condições de morte ou de fim da simulação.

- **check_death_and_full**:
- Monitora o estado da simulação, verificando se algum filósofo morreu ou se todos os filósofos atingiram o número de refeições necessárias. Se algum deles morrer, a simulação é interrompida.

- **cleanup_simulation**:
- Aguarda o término de todas as threads e destrói os mutexes criados.
### Arquivo msg_error.c

- **handle_error**:
- Exibe mensagens de erro apropriadas para diferentes problemas, como erros de argumento ou falha na inicialização de mutexes, threads ou alocação de memória.

### Arquivo start.c

- **init_mutexes**: 
- Inicializa todos os mutexes necessários para os garfos, controle de refeições e controle de escrita.

- **init_simulation**:
- Função principal de inicialização que faz o parsing dos argumentos da linha de comando e configura as estruturas de dados da simulação e dos filósofos.

- **setup_philos**:
- Prepara as estruturas de dados para cada filósofo, associando-os aos garfos à sua esquerda e direita.
### Arquivo utils.c

- **ft_atoi**:
- Converte uma string em um inteiro, semelhante à função atoi da biblioteca padrão C.

- **get_current_time**:
- Retorna o tempo atual em milissegundos desde a época (1970).

- **time_diff**:
- Calcula a diferença entre dois valores de tempo.

### Arquivo philo_utils.c

- **log_action**:
- Função que imprime as ações dos filósofos no formato: timestamp philosopher_id action. É protegida por um mutex para evitar condições de corrida durante a escrita no terminal.

- **sleep_for**:
- Faz o filósofo "dormir" por um período específico de tempo. A função pode ser interrompida se algum filósofo morrer.

- **mark_all_full**:
- Marca a simulação como concluída quando todos os filósofos atingem o número necessário de refeições.

### Arquivo philo_actions.c

- **philo_sleeps_and_thinks**:
- Simula as ações de dormir e pensar de um filósofo. Verifica se algum filósofo morreu durante essas ações.

- **philo_eats**:
- Simula a ação de comer de um filósofo, incluindo o bloqueio dos mutexes dos garfos, a atualização do tempo da última refeição e a contagem de refeições.

### Arquivo simulation.c

- **check_death_and_full**:
- Monitora se algum filósofo morreu ou se todos atingiram o número de refeições necessárias. Se todos os filósofos tiverem completado as refeições, marca a flag all_full como verdadeiro.

- **launch_simulation**:
- Inicializa a simulação, cria as threads de filósofos e aguarda o término da simulação, seja por morte ou por todos estarem satisfeitos.

## Considerações Finais
- Este projeto simula o comportamento de filósofos em um cenário de concorrência, abordando problemas como deadlocks e race conditions. Cada função foi cuidadosamente implementada para evitar problemas de concorrência e garantir que o comportamento esperado seja seguido.

### Sinta-se à vontade para modificar ou melhorar o código conforme necessário!
