/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:36:21 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 17:36:23 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static t_stack	*find_next_unindexed_min(t_stack **stack)
{
	t_stack	*lst;
	t_stack	*lst_min;
	int		min;

	if (!(*stack))
		return (NULL);
	min = 0;
	lst_min = NULL;
	lst = *stack;
	while (lst)
	{
		if ((lst->index == -1) && (!min || lst->content < lst_min->content))
		{
			lst_min = lst;
			min = 1;
		}
		lst = lst->next;
	}
	return (lst_min);
}

void	index_all_elements_by_content(t_stack **stack)
{
	t_stack	*lst;
	int		index;

	index = 0;
	lst = find_next_unindexed_min(stack);
	while (lst)
	{
		lst->index = index++;
		lst = find_next_unindexed_min(stack);
	}
}
