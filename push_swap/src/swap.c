/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:08:34 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 18:08:45 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	swap(t_stack **stack)
{
	int	index;
	int	content;

	if (!(*stack)->next)
		return ;
	content = (*stack)->next->content;
	index = (*stack)->next->index;
	(*stack)->next->content = (*stack)->content;
	(*stack)->next->index = (*stack)->index;
	(*stack)->content = content;
	(*stack)->index = index;
}

void	sa(t_stack **stack)
{
	swap(stack);
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_stack **stack)
{
	swap(stack);
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_stack **a_stack, t_stack **b_stack)
{
	swap(a_stack);
	swap(b_stack);
	ft_putstr_fd("ss\n", 1);
}
