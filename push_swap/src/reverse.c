/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:58:49 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 17:58:53 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	reverse(t_stack **stack)
{
	t_stack	*lst;

	if (!(*stack) || !(*stack)->next)
		return ;
	lst = lst_last(*stack);
	lst->prev->next = NULL;
	lst->prev = NULL;
	lst->next = *stack;
	(*stack)->prev = lst;
	*stack = (*stack)->prev;
}

void	rra(t_stack **stack)
{
	reverse(stack);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack **stack)
{
	reverse(stack);
	ft_putstr_fd("rra\n", 1);
}

void	rrr(t_stack **a_stack, t_stack **b_stack)
{
	reverse(a_stack);
	reverse(b_stack);
	ft_putstr_fd("rrr\n", 1);
}
