/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_initstack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:35:26 by tales             #+#    #+#             */
/*   Updated: 2024/06/22 18:59:27 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	validate_and_add_to_stack(char **split, t_stack **a_stack)
{
	long	num;
	int		i;

	i = 0;
	while (split[i])
	{
		if (!is_number(split[i]) || ft_strlen(split[i]) == 0)
		{
			free_split(split);
			ps_stackclear(a_stack);
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		num = ft_atol(split[i]);
		if (num > INT_MAX || num < INT_MIN)
		{
			free_split(split);
			ps_stackclear(a_stack);
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		lst_addback(a_stack, lst_new(ft_atoi(split[i])));
		i++;
	}
	return (1);
}

int	ps_initstack(int ac, char **av, t_stack **a_stack)
{
	char	**split;
	int		i;

	i = 1;
	while (i < ac)
	{
		split = ft_split(av[i], ' ');
		if (!split || !validate_and_add_to_stack(split, a_stack))
		{
			free_split(split);
			ps_stackclear(a_stack);
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		free_split(split);
		i++;
	}
	return (1);
}
