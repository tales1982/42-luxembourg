/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:05:22 by tales             #+#    #+#             */
/*   Updated: 2024/08/21 21:01:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_simulation sim;
    int ret;

    if (argc != 5 && argc != 6)
        return (handle_error(1));
    
    ret = init_simulation(&sim, argv);
    if (ret != 0)
        return ret;
    
    if (launch_simulation(&sim))
        return (handle_error(3));
    
    return (0);
}

/*
	saida ./nome_do_programa 3 800 200 200
 */