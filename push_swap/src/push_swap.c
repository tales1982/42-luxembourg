/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:30 by tlima-de          #+#    #+#             */
/*   Updated: 2024/06/22 18:59:40 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort_two_elements(t_stack **a_stack)
{
	if ((*a_stack)->content > (*a_stack)->next->content)
		sa(a_stack);
}

int	main(int ac, char **av)
{
	t_stack	*a_stack;
	t_stack	*b_stack;

	if (ac < 2)
	{
		ft_putstr_fd("\n", 2);
		return (1);
	}
	a_stack = NULL;
	b_stack = NULL;
	if (ps_initstack(ac, av, &a_stack) == 0 || ps_check_dup(a_stack) == -1)
		print_error_and_exit(&a_stack);
	index_all_elements_by_content(&a_stack);
	if (is_sorted(&a_stack) == 1)
		ps_stackclear(&a_stack);
	if (get_stack_size(a_stack) == 2)
		sort_two_elements(&a_stack);
	else if (get_stack_size(a_stack) <= 5)
		conditional_sort_based_on_size(&a_stack, &b_stack);
	else
		radix_sort(&a_stack, &b_stack);
	ps_stackclear(&a_stack);
	ps_stackclear(&b_stack);
	return (0);
}
