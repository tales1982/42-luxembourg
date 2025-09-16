// #### Exercício 1: Estrutura Básica da Classe
// **Nível: Iniciante**
//  **Objetivo** : Implemente a estrutura básica da classe bigint com:
//      ° Construtor padrão (inicializa como "0"). --> OK
//      ° Construtor a partir de um unsigned int (converte para string). --> OK
//      ° Construtor de cópia. --> OK
//      ° Operador de atribuição (=). --> OK
//      ° Método getStr() para retornar a string. --> OK
//      ° Sobrecarga do operador << para impressão (saída do número como está, sem zeros à esquerda ainda).
//
// **Teste** : Use a primeira parte do SUBJECT MAIN (impressão de a, b, c, d, e).

#include <iostream>
#include "Bigint.hpp"

int main(int ac, void **av) 
{
    (void)ac; 
    (void)av;

    Bigint a;            // "0"
    Bigint b(42);        // "42"
    Bigint c(a);         // cópia
    Bigint d = b;        // cópia
    Bigint e; e = b;     // atribuição

    std::cout << "a=" << a << "\n";
    std::cout << "b=" << b << "\n";
    std::cout << "c=" << c << "\n";
    std::cout << "d=" << d << "\n";
    std::cout << "e=" << e << "\n";
}