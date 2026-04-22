/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:34:53 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:25:16 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_arguments(t_simulation *sim, char **argv)
{
	sim->num_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	sim->all_full = 0;
	sim->someone_died = 0;
	if (sim->num_philos < 1 || sim->time_to_die < 0 || sim->time_to_eat < 0
		|| sim->time_to_sleep < 0 || sim->num_philos > 250)
		return (handle_error(1));
	if (argv[5])
	{
		sim->meals_required = ft_atoi(argv[5]);
		if (sim->meals_required <= 0)
			return (handle_error(1));
	}
	else
		sim->meals_required = -1;
	return (0);
}

static int	setup_philos(t_simulation *sim)
{
	int	i;

	i = sim->num_philos;
	while (--i >= 0)
	{
		sim->philos[i].id = i;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].left_fork_id = i;
		sim->philos[i].right_fork_id = (i + 1) % sim->num_philos;
		sim->philos[i].last_meal_time = 0;
		sim->philos[i].sim = sim;
	}
	if (sim->num_philos == 1)
	{
		sim->philos[0].left_fork_id = 0;
		sim->philos[0].right_fork_id = -1;
	}
	return (0);
}

int	init_mutexes(t_simulation *sim)
{
	int	i;

	i = sim->num_philos;
	while (--i >= 0)
		if (pthread_mutex_init(&(sim->forks[i]), NULL))
			return (1);
	if (pthread_mutex_init(&(sim->write_lock), NULL)
		|| pthread_mutex_init(&(sim->meal_check), NULL))
		return (1);
	return (0);
}

int	init_simulation(t_simulation *sim, char **argv)
{
	if (parse_arguments(sim, argv))
		return (1);
	if (init_mutexes(sim))
		return (handle_error(2));
	return (setup_philos(sim));
}
