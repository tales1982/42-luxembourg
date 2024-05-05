#ifndef CABECARIO_H
# define CABECARIO

/*************** LIBRARIES *************** */

# include <stdio.h>
#include <stdlib.h>

/****************** STRUCS *****************/
typedef struct no
{
	int			dado;
	struct no	*proximo;
}				No;

typedef struct
{
	No			*topo;
}				Pilha;

/* ****** FUNCTION DECLARATIONS *********** */
int				main(void);
int				ft_estaVazia(Pilha *p);
void			ft_imprimirPilha(Pilha *p);
void			ft_inicializarPilha(Pilha *p);
int				ft_pop(Pilha *p);
void			ft_push(Pilha *p, int valor);

#endif