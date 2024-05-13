/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:30 by tlima-de          #+#    #+#             */
/*   Updated: 2024/05/13 17:56:07 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ps_check_dup(t_stack *stack)
{
	int		tmp;
	t_stack	*dup;

	while (stack && stack->next)
	{
		tmp = stack->content;
		dup = stack;
		while (dup->next)
		{
			dup = dup->next;
			if (dup->content == tmp)
				return (-1);
		}
		stack = stack->next;
	}
	return (1);
}

static void	ps_stackclear(t_stack **stack)
{
	if (!stack || !(*stack))
		return ;
	ps_stackclear(&(*stack)->next);
	free(*stack);
	*stack = NULL;
}

static int	ps_initstack(int ac, char **av, t_stack **a_stack)
{
	int		i;
	int		j;
	char	**split;

	i = 1;
	while (i < ac)
	{
		j = 0;
		split = ft_split(av[i], ' ');
		if (!split[j])
			return (0);
		while (split[j])
		{
			if (ft_atol(split[j]) > INT_MAX || ft_atol(split[j]) < INT_MIN)
				return (0);
			lst_addback(a_stack, lst_new(ft_atoi(split[j])));
			j++;
		}
		free_split(split);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_stack	*a_stack;
	t_stack	*b_stack;

	if (ac == 1)
		return (ft_putstr_fd("Error\n", 1));
	a_stack = NULL;
	b_stack = NULL;
	if (ps_initstack(ac, av, &a_stack) == 0 || ps_check_dup(a_stack) == -1)
		return (ft_putstr_fd("Error\n", 1));
	index_all_elements_by_content(&a_stack);
	if (is_sorted(&a_stack) != 1)
	{
		if (get_stack_size(a_stack) <= 5)
		{
			conditional_sort_based_on_size(&a_stack, &b_stack);
		}
		else
		{
			radix_sort(&a_stack, &b_stack);
		}
	}
	ps_stackclear(&a_stack);
	ps_stackclear(&b_stack);
	return (0);
}
