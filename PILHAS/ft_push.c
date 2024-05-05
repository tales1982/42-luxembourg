
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:37:16 by tales             #+#    #+#             */
/*   Updated: 2024/05/05 13:40:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cabecario.h"


// Função para adicionar um elemento à pilha
void	ft_push(Pilha *p, int valor)
{
	No *novo = malloc(sizeof(No));
	if (novo == NULL)
	{
		printf("\nErro ao alocar a memoria...\n");
		return ;
	}
	novo->dado = valor;
	novo->proximo = p->topo;
	p->topo = novo;
}