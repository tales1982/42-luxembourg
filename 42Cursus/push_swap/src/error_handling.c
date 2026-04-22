/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:50:18 by tales             #+#    #+#             */
/*   Updated: 2024/06/22 18:59:04 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_error_and_exit(t_stack **a_stack)
{
	ft_putstr_fd("Error\n", 2);
	ps_stackclear(a_stack);
	exit(1);
}
