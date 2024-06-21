/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:00:06 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 18:00:13 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_sorted(t_stack **stack)
{
	t_stack	*tmp;

	tmp = *stack;
	while (tmp && tmp->next)
	{
		if (tmp->index > tmp->next->index)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

void	rotate_to_position(t_stack **stack, int size, int position)
{
	if (position <= size / 2)
	{
		while (position--)
			ra(stack);
	}
	else
	{
		position = size - position;
		while (position--)
			rra(stack);
	}
}

int	is_order(t_stack **stack, int size)
{
	int		position;
	t_stack	*tmp;

	tmp = *stack;
	position = 0;
	while (tmp && tmp->index != 0)
	{
		position++;
		tmp = tmp->next;
	}
	if (is_sorted(stack) == 1)
	{
		rotate_to_position(stack, size, position);
		return (1);
	}
	return (0);
}

void	reset_index(t_stack **stack)
{
	t_stack	*lst;

	lst = *stack;
	while (lst)
	{
		lst->index = -1;
		lst = lst->next;
	}
	index_all_elements_by_content(stack);
}

void	rotate_to_min(t_stack **stack, int size)
{
	int		position;
	t_stack	*tmp;

	tmp = *stack;
	position = 0;
	while (tmp && tmp->index != 0)
	{
		position++;
		tmp = tmp->next;
	}
	rotate_to_position(stack, size, position);
}
