/*
 * Escreva um programa que pegue uma string e a exiba, substituindo cada uma de suas
letras pela próxima em ordem alfabética.

'z' torna-se 'a' e 'Z' torna-se 'A'. O caso permanece inalterado.

A saída será seguida por um \n.

Se o número de argumentos não for 1, o programa exibirá \n.
*/

#include <unistd.h>

void  rotone(char *str); 

int main(int argc, char **argv)
{
	if(argc <= 1)
		write(1,"\n", 1);
	else
	rotone(argv[1]);
	return (0);
	
}

void  rotone(char *str)
{

  int i = 0;
  
  while(str[i] != '\0')
  {
  	if(str[i] == 'z' || str[i] == 'Z')
  	{
  		str[i] -= 26;
  	}
  	else
	{
		str[i] += 1;
		write(1, &str[i], 1); 
		i++;
	}
  }
  
  write(1, "\n", 1);

}