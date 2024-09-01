/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:44:05 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:34:38 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos_states(t_simulation *sim)
{
	int	i;

	pthread_mutex_lock(&(sim->write_lock));
	printf("\n[Current state of philosophers]:\n");
	for (i = 0; i < sim->num_philos; i++)
	{
		printf("Philosopher %d: ", i + 1);
		if (time_diff(sim->philos[i].last_meal_time,
				get_current_time()) > sim->time_to_die)
			printf("dead\n");
		else if (sim->philos[i].last_meal_time
			+ sim->time_to_eat >= get_current_time())
			printf("eating\n");
		else if (sim->philos[i].last_meal_time + sim->time_to_eat
			+ sim->time_to_sleep >= get_current_time())
			printf("sleeping\n");
		else
			printf("thinking\n");
	}
	pthread_mutex_unlock(&(sim->write_lock));
}

void	check_death(t_simulation *sim, t_philosopher *philos)
{
	int	i;

	while (!sim->someone_died)
	{
		i = -1;
		while (++i < sim->num_philos && !sim->someone_died)
		{
			if (check_philo_death(sim, philos, i))
				break ;
		}
		if (check_all_philos_full(sim, philos))
			break ;
		usleep(1000);
	}
}
#include "philo.h"

int	check_philo_death(t_simulation *sim, t_philosopher *philo, int i)
{
	int	died;

	died = 0;
	pthread_mutex_lock(&(sim->meal_check));
	if (time_diff(philo[i].last_meal_time,
			get_current_time()) > sim->time_to_die)
	{
		log_action(sim, i, "died");
		sim->someone_died = 1;
		died = 1;
	}
	pthread_mutex_unlock(&(sim->meal_check));
	return (died);
}

int	check_all_philos_full(t_simulation *sim, t_philosopher *philos)
{
	int	philos_full;
	int	i;

	philos_full = 0;
	i = -1;
	while (++i < sim->num_philos)
	{
		pthread_mutex_lock(&(sim->meal_check));
		if (sim->meals_required > 0
			&& philos[i].meals_eaten >= sim->meals_required)
			philos_full++;
		pthread_mutex_unlock(&(sim->meal_check));
	}
	if (philos_full == sim->num_philos)
	{
		pthread_mutex_lock(&(sim->meal_check));
		sim->all_full = 1;
		pthread_mutex_unlock(&(sim->meal_check));
		return (1);
	}
	return (0);
}

int	launch_simulation(t_simulation *sim)
{
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = sim->philos;
	sim->start_time = get_current_time();
	while (i < sim->num_philos)
	{
		if (pthread_create(&(philos[i].thread_id), NULL, philo_thread,
				&(philos[i])))
			return (1);
		philos[i].last_meal_time = get_current_time();
		i++;
	}
	check_death(sim, sim->philos);
	cleanup_simulation(sim, philos);
	return (0);
}
