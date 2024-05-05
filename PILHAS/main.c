/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:41 by tales             #+#    #+#             */
/*   Updated: 2024/05/05 14:46:49 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cabecario.h"


int	main(void)
{
	Pilha p;
	ft_inicializarPilha(&p);
	ft_push(&p, 10);
	ft_push(&p, 20);
	ft_push(&p, 30);
	ft_imprimirPilha(&p);
	printf("Elemento desempilhado: %d\n", ft_pop(&p));
	ft_imprimirPilha(&p);
	return (0);
}