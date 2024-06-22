/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:50:18 by tales             #+#    #+#             */
/*   Updated: 2024/06/22 15:59:20 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_error_and_exit(t_stack **a_stack)
{
	ft_putstr_fd("Error\n", 2);
	//printf("Error function called.\n");//REMOVER
	ps_stackclear(a_stack);
	exit(1);
}