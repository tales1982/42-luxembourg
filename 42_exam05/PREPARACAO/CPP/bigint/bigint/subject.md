Nome da tarefa: bigint
Arquivos esperados: bigint.hpp, bigint.cpp

Na ciência da computação, um bignum é um objeto que representa um número de precisão arbitrária.
Isso é útil quando você deseja armazenar um número maior que SIZE_MAX sem qualquer perda de precisão.
Isso geralmente é feito armazenando um vetor (array) ou uma string contendo as diferentes “partes” do número.

Crie uma classe chamada bigint que irá armazenar um número inteiro sem sinal de precisão arbitrária.

Sua classe deve suportar:

adição,

comparação,

e “digitshift” (como bitshift, mas em vez de deslocar os bits você desloca os dígitos na base 10).

Exemplo:

(42 << 3 == 42000)

(1337 >> 2 == 13)

Seu bigint deve ser imprimível com o operador << (em base 10) e a saída não deve conter zeros à esquerda.


📌 Objetivo da tarefa

Você precisa criar uma classe em C++ chamada bigint capaz de trabalhar com números inteiros maiores do que o limite natural do tipo inteiro do C++ (SIZE_MAX).

Ou seja, quando um número é muito grande para caber em um int ou long long, você vai armazenar ele de outra forma (como string ou array de dígitos) para não perder precisão.

📌 O que sua classe precisa ter

Armazenar o número

Não pode usar int, long ou unsigned long como base principal, porque eles têm limite.

Em vez disso, guarde o número como string ou vetor de dígitos.

Exemplo: o número 12345 pode ser guardado como ['1','2','3','4','5'] ou como [5,4,3,2,1].

Operações obrigatórias

Adição (+) → sua classe deve permitir somar dois bigint.

Exemplo: bigint(42) + bigint(21) == bigint(63).

Comparação (<, <=, >, >=, ==, !=) → precisa conseguir comparar se um número é maior, menor ou igual ao outro.

Digitshift (<< e >>) → parecido com bitshift, mas em base 10:

42 << 3 == 42000 → desloca 3 casas decimais para a esquerda (multiplicação por 10³).

1337 >> 2 == 13 → desloca 2 casas decimais para a direita (divisão inteira por 100).

Impressão (<<)

Deve ser possível imprimir um bigint no std::cout.

Exemplo:

bigint a(42);
std::cout << a; // deve mostrar 42


Não pode aparecer zero à esquerda (exemplo: não pode imprimir 00042, tem que ser 42).

Funcionar com o main fornecido

O arquivo main que veio junto já tem vários testes: soma, incrementos (++), comparações, shifts.

A sua classe só passa no exercício se o main rodar sem erro e imprimir os resultados corretos.

📌 Em resumo:

Você vai implementar uma classe bigint que:
✅ guarda inteiros gigantes como string/array de dígitos.
✅ sabe fazer soma.
✅ sabe fazer comparações (<, >, ==, != ...).
✅ sabe fazer digitshift (<<, >>).
✅ imprime corretamente com std::cout.