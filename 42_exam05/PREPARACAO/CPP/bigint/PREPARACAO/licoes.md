#### Exercício 1: Estrutura Básica da Classe

**Nível: Iniciante**
 **Objetivo** : Implemente a estrutura básica da classe bigint com:

* Construtor padrão (inicializa como "0").
* Construtor a partir de um unsigned int (converte para string).
* Construtor de cópia.
* Operador de atribuição (=).
* Método getStr() para retornar a string.
* Sobrecarga do operador << para impressão (saída do número como está, sem zeros à esquerda ainda).

 **Teste** : Use a primeira parte do SUBJECT MAIN (impressão de a, b, c, d, e).

---

#### Exercício 2: Operadores de Adição

**Nível: Iniciante-Intermediário**
 **Objetivo** : Adicione os operadores de adição:

* operator+ (soma dois bigints).
* operator+= (adiciona outro bigint ao atual).
* Implemente a adição tratando strings como dígitos invertidos, considerando carry (vai-um). Inclua uma função auxiliar reverse para inverter strings.

 **Teste** : Adicione as linhas de adição do SUBJECT MAIN (a + b, c += a).

---

#### Exercício 3: Operadores de Incremento

**Nível: Intermediário**
 **Objetivo** : Implemente os operadores de incremento:

* Pré-incremento (++x).
* Pós-incremento (x++).
* Use a adição do Exercício 2.

 **Teste** : Adicione as linhas de incremento do SUBJECT MAIN (++b, b++).

---

#### Exercício 4: Deslocamento de Dígitos com Unsigned Int

**Nível: Intermediário**
 **Objetivo** : Implemente os operadores de deslocamento para unsigned int:

* << (adiciona n zeros no final).
* >> (remove os últimos n dígitos; retorna "0" se n >= comprimento).
  >>
  >
* <<= e >>= (atribuem o resultado ao objeto atual).

 **Teste** : Adicione as linhas de deslocamento do SUBJECT MAIN, como (b << 10) + 42.

---

#### Exercício 5: Deslocamento de Dígitos com Objeto BigInt

**Nível: Intermediário-Avançado**
 **Objetivo** : Sobrecarregue os operadores de deslocamento para aceitar outro bigint:

* <<, >>, <<=, >>=.
* Converta o bigint de entrada (outro.str) para unsigned int e reutilize os operadores do Exercício 4. Assuma que o número cabe em um unsigned int.

 **Teste** : Use os testes extras do segundo main, como x << y (x=12345678, y=5).

---

#### Exercício 6: Operadores de Comparação

**Nível: Avançado**
 **Objetivo** : Implemente todos os operadores de comparação:

* ==, !=, <, >, <=, >=.
* Compare primeiro pelo comprimento das strings, depois lexicograficamente se tiverem o mesmo comprimento.

 **Teste** : Adicione as linhas de comparação do SUBJECT MAIN e do main extra.

---

#### Exercício 7: Implementação Completa do BigInt

**Nível: Especialista**
 **Objetivo** : Implemente a classe bigint completa do zero, baseada no enunciado [PT]. Inclua:

* Construtores (padrão, unsigned int, cópia).
* Operador de atribuição.
* Operadores +, +=, ++ (pré/pós).
* Deslocamentos <<, >>, <<=, >>= (para unsigned int e bigint).
* Comparações ==, !=, <, >, <=, >=.
* Sobrecarga de << para impressão (sem zeros à esquerda).

 **Teste** : Ambos os mains devem funcionar exatamente como no original (sem zeros à esquerda, deslocamentos corretos).
