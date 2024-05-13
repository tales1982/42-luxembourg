/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:57:18 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 17:57:27 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	calculate_max_index_bits(t_stack **stack)
{
	t_stack	*current_node;
	int		max;
	int		max_b;

	current_node = *stack;
	max = current_node->index;
	max_b = 0;
	while (current_node)
	{
		if (current_node->index > max)
			max = current_node->index;
		current_node = current_node->next;
	}
	while ((max >> max_b) != 0)
		max_b++;
	return (max_b);
}

int get_stack_size(t_stack *stack) {
    int count;
	
	count = 0;
    while (stack) {
        count++;
        stack = stack->next;
    }
    return count;
}

void	radix_sort(t_stack**a_stack, t_stack **b_stack)
{
	t_stack	*lst;
	int		i;
	int		j;
	int		size;
	int		max_b;

	lst = *a_stack;
	size = get_stack_size(*a_stack);
	max_b = calculate_max_index_bits(a_stack);
	i = -1;
	while (++i < max_b)
	{
		j = -1;
		while (++j < size)
		{
			lst = *a_stack;
			if (((lst->index >> i) & 1) == 0)
				pb(a_stack, b_stack);
			else
				ra(a_stack);
		}
		while (get_stack_size(*b_stack) != 0)
			pa(a_stack, b_stack);
	}
}
