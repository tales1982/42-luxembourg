/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:27:27 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 18:27:33 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_stack **stack)
{
	t_stack	*lst;

	if (!(*stack) || !(*stack)->next)
		return ;
	lst = lst_last(*stack);
	lst->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	lst->next->prev = lst;
	lst->next->next = NULL;
}

void	ra(t_stack **stack)
{
	rotate(stack);
	ft_putstr_fd("ra\n", 1);
}

void	rb(t_stack **stack)
{
	rotate(stack);
	ft_putstr_fd("rb\n", 1);
}

void	rr(t_stack **a_stack, t_stack **b_stack)
{
	rotate(a_stack);
	rotate(b_stack);
	ft_putstr_fd("rr\n", 1);
}
