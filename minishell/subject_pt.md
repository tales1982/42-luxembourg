# Minishell: Tão bonita quanto um shell

- Resumo: Este projeto é sobre criar um shell simples. Sim, o seu próprio pequeno bash. Você aprenderá muito sobre processos e descritores de arquivos.

- Versão: 7.1

## Conteúdo I. Introdução
### II. Instruções Comuns
### III. Parte Obrigatória
### IV. Parte Bônus
### V. Submissão e Avaliação por Pares

- Capítulo I: Introdução A existência dos shells está ligada à própria existência da TI. Na época, todos os desenvolvedores concordaram que comunicar-se com um computador usando interruptores alinhados de 1/0 era extremamente irritante. Era lógico que eles tivessem a ideia de criar um software para se comunicar com um computador usando linhas de comando interativas em uma linguagem um pouco próxima à linguagem humana. Graças ao Minishell, você poderá viajar no tempo e voltar aos problemas que as pessoas enfrentavam quando o Windows não existia.

- Capítulo II: Instruções Comuns

Seu projeto deve ser escrito em C.
Seu projeto deve ser escrito de acordo com a Norm. Se você tiver arquivos/funções bônus, eles serão incluídos na verificação da Norm, e você receberá 0 se houver um erro de Norm.
Suas funções não devem sair inesperadamente (falha de segmentação, erro de barramento, double free, etc.), exceto em comportamentos indefinidos. Se isso acontecer, seu projeto será considerado não funcional e receberá 0 durante a avaliação.
Todo espaço de memória alocado no heap deve ser liberado corretamente quando necessário. Nenhum vazamento de memória será tolerado.
Se o enunciado exigir, você deve enviar um Makefile que compile seus arquivos-fonte para a saída requerida com as flags -Wall, -Wextra e -Werror, usando cc, e seu Makefile não deve relinkar.
Seu Makefile deve conter pelo menos as regras $(NAME), all, clean, fclean e re.
Para incluir bônus no seu projeto, você deve incluir uma regra bonus no seu Makefile, que adicionará todos os diferentes cabeçalhos, bibliotecas ou funções que são proibidos na parte principal do projeto. Os bônus devem estar em um arquivo separado _bonus.{c/h}, se o enunciado não especificar outra coisa. A avaliação das partes obrigatória e bônus é feita separadamente.
Se o seu projeto permitir o uso da sua libft, você deve copiar suas fontes e seu Makefile associado em uma pasta libft com seu Makefile associado. O Makefile do seu projeto deve compilar a biblioteca usando seu Makefile e, em seguida, compilar o projeto.
Nós encorajamos você a criar programas de teste para o seu projeto, mesmo que esse trabalho não precise ser enviado e não seja avaliado. Isso lhe dará a chance de testar facilmente o seu trabalho e o trabalho de seus colegas. Você achará esses testes especialmente úteis durante sua defesa. De fato, durante a defesa, você é livre para usar seus testes e/ou os testes do colega que você está avaliando.
Submeta seu trabalho ao repositório git atribuído a você. Apenas o trabalho no repositório git será avaliado. Se o Deepthought for designado para avaliar seu trabalho, isso será feito após suas avaliações por pares. Se ocorrer um erro em qualquer seção do seu trabalho durante a avaliação do Deepthought, a avaliação será interrompida.
Capítulo III: Parte Obrigatória

***Nome do programa***: minishell
***Arquivos a serem entregues***: Makefile, *.h, *.c
***Makefile***: NAME, all, clean, fclean, re
***Argumentos***:
***Funções externas***: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
***Libft autorizada***: Sim

- Descrição:
Escreva um shell.
Seu shell deve:

- Exibir um prompt enquanto aguarda um novo comando.
Ter um histórico funcional.
Buscar e executar o executável correto (com base na variável PATH ou usando um caminho relativo ou absoluto).
Evitar o uso de mais de uma variável global para indicar um sinal recebido. Considere as implicações: essa abordagem garante que seu manipulador de sinais não acesse suas principais estruturas de dados. Tenha cuidado. Esta variável global não pode fornecer qualquer outra informação ou acesso a dados além do número de um sinal recebido. Portanto, o uso de estruturas do tipo "norm" no escopo global é proibido.
Não interpretar aspas não fechadas ou caracteres especiais que não são exigidos pelo enunciado, como \ (barra invertida) ou ; (ponto e vírgula).
Manipular aspas simples ('), que devem impedir que o shell interprete os metacaracteres na sequência citada.
Manipular aspas duplas ("), que devem impedir que o shell interprete os metacaracteres na sequência citada, exceto o $ (sinal de dólar).
Implementar redirecionamentos:
< deve redirecionar a entrada.
deve redirecionar a saída.

<< deve ser dado um delimitador, e então ler a entrada até que uma linha contendo o delimitador seja vista. No entanto, não precisa atualizar o histórico!
deve redirecionar a saída em modo de anexação.

Implementar pipes (caractere |). A saída de cada comando no pipeline é conectada à entrada do próximo comando por meio de um pipe.
Manipular variáveis de ambiente ($ seguido de uma sequência de caracteres), que devem se expandir para seus valores.
Manipular $? que deve se expandir para o status de saída do pipeline em primeiro plano executado mais recentemente.
Manipular ctrl-C, ctrl-D e ctrl-\ que devem se comportar como no bash.
No modo interativo:
1. ctrl-C exibe um novo prompt em uma nova linha.
2. ctrl-D sai do shell.
3. ctrl-\ não faz nada.
4. Seu shell deve implementar os seguintes comandos internos:
5. echo com a opção -n
6. cd com apenas um caminho relativo ou absoluto
7. pwd sem opções
8. export sem opções
9. unset sem opções
10. env sem opções ou argumentos
11. exit sem opções
- A função readline() pode causar vazamentos de memória. Você não precisa corrigi-los. Mas isso não significa que o seu próprio código, sim, o código que você escreveu, pode ter vazamentos de memória. Você deve se limitar à descrição do enunciado. Qualquer coisa que não seja solicitada não é necessária. Se você tiver alguma dúvida sobre um requisito, tome o bash como referência.