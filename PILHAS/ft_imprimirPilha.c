
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imprimirPilha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:23:28 by tales             #+#    #+#             */
/*   Updated: 2024/05/05 14:23:43 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cabecario.h"

// Função para imprimir os elementos da pilha
void	ft_imprimirPilha(Pilha *p)
{
	No	*atual;

	atual = p->topo;
	printf("Topo -> ");
	while (atual != NULL)
	{
		printf("%d -> ", atual->dado);
		atual = atual->proximo;
	}
	printf("NULL\n");
}
