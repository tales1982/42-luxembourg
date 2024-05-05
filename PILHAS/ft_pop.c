
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:14:51 by tales             #+#    #+#             */
/*   Updated: 2024/05/05 14:14:52 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cabecario.h"


// Função para remover um elemento da pilha
int	ft_pop(Pilha *p)
{
	No *temp;
	int valor;
	if (ft_estaVazia(p))
	{
		printf("\nPilha Vazia..\n");
		return (-1); // Retornando -1 para indicar que a pilha está vazia
	}
	temp = p->topo;
	valor = temp->dado;
	p->topo = temp->proximo;
	free(temp);
	return (valor);
}