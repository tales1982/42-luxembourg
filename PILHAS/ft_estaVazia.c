
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_estaVazia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:49:18 by tales             #+#    #+#             */
/*   Updated: 2024/05/05 13:49:19 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Função para verificar se a pilha está vazia

#include "cabecario.h"

int ft_estaVazia(Pilha *p)
{
    return(p->topo == NULL);
}
