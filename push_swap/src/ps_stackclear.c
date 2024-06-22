/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stackclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:44:38 by tales             #+#    #+#             */
/*   Updated: 2024/06/22 15:25:54 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void ps_stackclear(t_stack **stack)
{
    if (!stack || !(*stack))
        return;
    ps_stackclear(&(*stack)->next);
    free(*stack);
    *stack = NULL;
}
