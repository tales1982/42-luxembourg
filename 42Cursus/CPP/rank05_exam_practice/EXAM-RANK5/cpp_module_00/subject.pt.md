Enunciado do Projeto
Nome do Projeto: cpp_module_00
Arquivos Esperados: Warlock.cpp Warlock.hpp
Crie uma classe Warlock. Ela deve seguir a forma de Coplien.
A classe terá os seguintes atributos privados:
nome (string)
título (string)
Como são privados, você precisará escrever os seguintes getters:
getName, retorna uma referência para uma string constante
getTitle, retorna uma referência para uma string constante
Ambas as funções precisam ser chamadas em um Warlock constante.
Crie o seguinte setter:
setTitle, retorna void e recebe uma referência para uma string constante
O Warlock também terá, além do que é exigido pela forma de Coplien, um construtor que recebe, nessa ordem, seu nome e título. O Warlock não poderá ser copiado, instanciado por cópia ou instanciado sem um nome e um título.
Por exemplo:
Warlock bob; //Não compila
Warlock bob("Bob", "o magnífico"); //Compila
Warlock jim("Jim", "o nauseante"); //Compila
bob = jim; //Não compila
Warlock jack(jim); //Não compila
Quando criado, o Warlock diz:
`<NOME>`: Este parece ser outro dia entediante.
Obviamente, sempre que usarmos espaços reservados como `<NOME>`, <TÍTULO>, etc... nas saídas, você substituirá pelos valores apropriados. Sem os < e >.
Quando ele morre, diz:
`<NOME>`: Meu trabalho aqui está feito!
Nosso Warlock também precisa ser capaz de se apresentar, enquanto se gaba com toda a sua força.
Então você escreverá a seguinte função:
void introduce() const;
Ela precisa exibir:
`<NOME>`: Eu sou `<NOME>`, <TÍTULO>!std::
Aqui está um exemplo de uma função main de teste e sua saída associada:
C++
int main()
{
  Warlock const richard("Richard", "Senhor(a) do Magma");
  richard.introduce();
  std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

  Warlock* jack = new Warlock("Jack", "o Longo");
  jack->introduce();
  jack->setTitle("o Poderoso");
  jack->introduce();

  delete jack;

  return (0);
}
~$ ./a.out | cat -e
Richard: Este parece ser outro dia entediante.$
Richard: Eu sou Richard, Senhor(a) do Magma!$
Richard - Senhor(a) do Magma$
Jack: Este parece ser outro dia entediante.$
Jack: Eu sou Jack, o Longo!$
Jack: Eu sou Jack, o Poderoso!$
Jack: Meu trabalho aqui está feito!$
Richard: Meu trabalho aqui está feito!$
Implementação
Warlock.hpp
C++
#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include `<iostream>`
#include `<string>`

class Warlock {
private:
    std::string name;
    std::string title;

public:
    Warlock(std::string const& name, std::string const& title);
    ~Warlock();

    Warlock(Warlock const&) = delete;
    Warlock& operator=(Warlock const&) = delete;

    std::string const& getName() const;
    std::string const& getTitle() const;

    void setTitle(std::string const& title);

    void introduce() const;
};

#endif
Warlock.cpp
C++
#include "Warlock.hpp"

Warlock::Warlock(std::string const& name, std::string const& title) : name(name), title(title) {
    std::cout << name << ": Este parece ser outro dia entediante." << std::endl;
}

Warlock::~Warlock() {
    std::cout << name << ": Meu trabalho aqui está feito!" << std::endl;
}

std::string const& Warlock::getName() const {
    return name;
}

std::string const& Warlock::getTitle() const {
    return title;
}

void Warlock::setTitle(std::string const& newTitle) {
    title = newTitle;
}

void Warlock::introduce() const {
    std::cout << name << ": Eu sou " << name << ", " << title << "!" << std::endl;
}
main.cpp (para teste)
C++
#include "Warlock.hpp"

int main() {
    Warlock const richard("Richard", "Senhor(a) do Magma");
    richard.introduce();
    std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

    Warlock* jack = new Warlock("Jack", "o Longo");
    jack->introduce();
    jack->setTitle("o Poderoso");
    jack->introduce();

    delete jack;

    return 0;
}
Essa implementação segue as especificações fornecidas, garantindo que a classe Warlock tenha os atributos privados name e title, com getters e setters apropriados. O construtor e destrutor são implementados para imprimir as mensagens especificadas. A função introduce é usada para apresentar o Warlock. Além disso, a classe é projetada para não permitir cópias ou instanciação sem nome e título.
