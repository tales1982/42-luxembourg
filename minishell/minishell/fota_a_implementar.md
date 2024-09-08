## Requisitos Cumpridos:
- 1. **Prompt de comando**: Você exibe um prompt com a função readline(), o que está correto. O prompt reaparece após cada comando, exceto quando Ctrl+D é pressionado, o que é esperado.
- 2. **Histórico de comandos**: O uso de readline() junto com add_history() permite manter o histórico de comandos, o que é um ponto importante para atender o requisito.
- 3. **Execução de comandos**: A função search_path() localiza o executável correto no caminho do sistema usando a variável PATH, ou permite a execução de comandos com caminho relativo ou absoluto.
- **Variável global para sinal**: O handle_sigint() lida com sinais como Ctrl+C e não interfere nas estruturas principais do shell. Como você só usa uma variável global (a environ, que é externa e permitida), isso está em conformidade com as regras.
- **Redirecionamento básico e pipes**: Você já implementou parcialmente a execução com pipes usando a função pipe() e redirecionamento através de dup2() e execve(). Isso cobre parte do requisito de redirecionamento de entrada e saída entre comandos em um pipeline.

## O que ainda precisa ser implementado ou ajustado:
**Redirecionamento de entrada e saída**:

- Você deve implementar o suporte para redirecionar entrada (<) e saída (> e >>) conforme descrito no enunciado. Para isso, você pode usar as funções open(), dup2(), e close() para abrir arquivos e redirecionar os fluxos de entrada e saída.
O redirecionamento << com delimitador (heredoc) também precisa ser implementado, onde a entrada continua até o delimitador ser encontrado.
Interpretação de aspas:

- Seu shell precisa lidar com aspas simples (') e duplas ("). Aspas simples devem impedir a interpretação de qualquer caractere especial, enquanto aspas duplas ainda devem interpretar o $ para variáveis de ambiente.
Implementação de builtins:

- Você já implementou o comando cd, mas ainda faltam os outros builtins exigidos: echo, pwd, export, unset, env e exit.
A função echo precisa suportar a flag -n, que impede a nova linha no final.
O comando export deve manipular variáveis de ambiente, adicionando ou modificando-as.
Manuseio de variáveis de ambiente:

- Seu shell precisa reconhecer e expandir variáveis de ambiente, por exemplo, echo $HOME deve imprimir o valor da variável de ambiente HOME.
Comportamento dos sinais:

- O shell deve lidar com Ctrl+D (para sair) e Ctrl+\ (que não deve fazer nada) corretamente. Atualmente, o Ctrl+D encerra o shell, o que está correto, mas Ctrl+\ precisa ser tratado para não fazer nada.
Aspas não fechadas e caracteres especiais:

- Seu shell precisa detectar aspas não fechadas e não interpretar caracteres especiais como \ e ;, que não são exigidos pelo enunciado.
Considerações sobre o bonus:
Os operadores && e ||, bem como o uso de parênteses para definir a prioridade, fazem parte da avaliação bônus. Além disso, o suporte para wildcards (*) no diretório atual também é avaliado como parte do bônus.
