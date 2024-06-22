/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:35:33 by tales             #+#    #+#             */
/*   Updated: 2024/06/22 15:24:38 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int ps_check_dup(t_stack *stack)
{
    t_stack *current;
    t_stack *runner;

    current = stack;
    while (current)
    {
        runner = current->next;
        while (runner)
        {
            if (current->content == runner->content)
                return (-1);
            runner = runner->next;
        }
        current = current->next;
    }
    return (1);
}
