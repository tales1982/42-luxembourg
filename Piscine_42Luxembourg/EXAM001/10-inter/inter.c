/*
 Écrivez un programme qui prend deux chaînes et affiche, 
 sans doubles, le caractères qui apparaissent dans les deux chaînes, 
 dans l'ordre dans lequel ils apparaissent dans la première un.

L'affichage sera suivi d'un \n.

Si le nombre d'arguments n'est pas 2, le programme affiche \n.
 */

#include <unistd.h>

void	inter(char *s1, char *s2);

int	main()
{
  char	n[] = "padinton";
  char	n2[] = "paqefwtdjetyiytjneytjoeyjnejeyj";
   
  
  inter(n,n2);
	return (0);
}

void inter(char *s1, char *s2)
{

}
