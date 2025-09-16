/* 
#### Exercício 2: Operadores de Adição
**Nível: Iniciante-Intermediário**
 **Objetivo** : Adicione os operadores de adição:
    ° operator+ (soma dois bigints).
    ° operator+= (adiciona outro bigint ao atual).
    ° Implemente a adição tratando strings como dígitos invertidos, considerando carry (vai-um). Inclua uma função auxiliar reverse para inverter strings.

 **Teste** : Adicione as linhas de adição do SUBJECT MAIN (a + b, c += a).
 */

 #include <iostream>
 #include "Bigint.hpp"

 int main(int ac, char **av)
 {
    (void)ac;
    (void)av;

    Bigint a;
    Bigint b(42);
    Bigint c (b);
    Bigint d = c;
    Bigint e; e = d;


    std::cout << "a=" << a << "\n";
    std::cout << "b=" << b << "\n";
    std::cout << "c=" << c << "\n";
    std::cout << "d=" << d << "\n";
    std::cout << "e=" << e << "\n";


 }