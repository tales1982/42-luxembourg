#include "Warlock.hpp"

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