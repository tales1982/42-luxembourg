
# Valgrind

## O que é Valgrind?
Valgrind é uma ferramenta de software que fornece um conjunto de instrumentação dinâmica para programas. É amplamente utilizado para detectar vazamentos de memória, erros de execução e para ajudar na análise de desempenho.

## Instalação do Valgrind

Valgrind funciona em sistemas UNIX-like, incluindo Linux e macOS (se disponível). Siga as instruções abaixo para instalá-lo no seu sistema:

### Debian/Ubuntu
```bash
sudo apt-get install valgrind
```
# macOS
```bash
brew install valgrind
```
# Uso do Valgrind
Para executar o Valgrind e verificar se há vazamentos de memória em seu programa, use o seguinte comando:

```bash
valgrind --leak-check=full ./seu_programa
```
Este comando executa o seu programa sob o ambiente do Valgrind, rastreando todas as alocações de memória para garantir que não haja vazamentos. 
O Valgrind imprimirá um relatório no final da execução do programa, indicando se algum vazamento de memória foi encontrado.

# Exemplo de Uso com o push_swap
Se você deseja verificar o programa push_swap com um conjunto específico de entradas, pode usar o comando:

```bash
valgrind --leak-check=full ./push_swap 5 1 3 2 4
```
Este comando é particularmente útil para testar se o push_swap está lidando corretamente com a memória ao processar as entradas especificadas. 
Ele ajudará a identificar vazamentos de memória nos arquivos do programa, garantindo a estabilidade e a eficiência do software.