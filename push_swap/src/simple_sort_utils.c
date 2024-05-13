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
/*
int	is_sorted(t_stack **stack)
{
	t_stack	*tmp;

	tmp = *stack;
	while (tmp->next)
	{
		if (tmp->index > tmp->next->index)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}

int is_sorted(t_stack **stack) {
    t_stack *tmp = *stack;
    while (tmp && tmp->next) {
        if (tmp->index > tmp->next->index)
            return (-1);
        tmp = tmp->next;
    }
    return (1);
}

int	is_order(t_stack **stack, int size)
{
	int	i;

	i = 0;
	while ((*stack)->index != 0)
	{
		rotate(stack);
		i++;
	}
	if (is_sorted(stack) == 1)
	{
		if (i > (size / 2))
		{
			if (size == 5 && i == 3)
				ft_putstr_fd("rra\n", 1);
			ft_putstr_fd("rra\n", 1);
		}
		else
			while (i-- > 0)
				ft_putstr_fd("ra\n", 1);
		return (1);
	}
	else
		while (i-- > 0)
			reverse(stack);
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
	int	i;

	i = 0;
	while ((*stack)->index != 0)
	{
		rotate(stack);
		i++;
	}
	if ((i > (size / 2)))
	{
		if (size == 5 && i == 3)
			ft_putstr_fd("rra\n", 1);
		ft_putstr_fd("rra\n", 1);
	}
	else
	{
		while (i > 0)
		{
			ft_putstr_fd("ra\n", 1);
			i--;
		}
	}
}
*/

#include "../push_swap.h"

int is_sorted(t_stack **stack) {
    t_stack *tmp = *stack;
    while (tmp && tmp->next) {
        if (tmp->index > tmp->next->index)
            return (-1);
        tmp = tmp->next;
    }
    return (1);
}

void rotate_to_position(t_stack **stack, int size, int position) {
    if (position <= size / 2) {
        while (position--)
            ra(stack);
    } else {
        position = size - position;
        while (position--)
            rra(stack);
    }
}

int is_order(t_stack **stack, int size) {
    int position = 0;
    t_stack *tmp = *stack;

    while (tmp && tmp->index != 0) {
        position++;
        tmp = tmp->next;
    }

    if (is_sorted(stack) == 1) {
        rotate_to_position(stack, size, position);
        return (1);
    }

    return (0);
}

void reset_index(t_stack **stack) {
    t_stack *lst = *stack;
    while (lst) {
        lst->index = -1;
        lst = lst->next;
    }
    index_all_elements_by_content(stack);
}

void rotate_to_min(t_stack **stack, int size) {
    int position = 0;
    t_stack *tmp = *stack;

    while (tmp && tmp->index != 0) {
        position++;
        tmp = tmp->next;
    }
    rotate_to_position(stack, size, position);
}
