/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:40:48 by tlima-de          #+#    #+#             */
/*   Updated: 2024/06/22 14:34:45 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"


static void push(t_stack **a_stack, t_stack **b_stack) {
    t_stack *tmp;

    if (!b_stack || !(*b_stack))
        return;
    tmp = (*b_stack)->next;
    lst_addfront(a_stack, *b_stack);
    *b_stack = tmp;
    if (*b_stack)
        (*b_stack)->prev = NULL;
}
void	pa(t_stack**a_stack, t_stack **b_stack)
{
	push(a_stack, b_stack);
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_stack **a_stack, t_stack **b_stack)
{
	push(b_stack, a_stack);
	ft_putstr_fd("pb\n", 1);
}
