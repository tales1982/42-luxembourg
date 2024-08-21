/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:44:05 by tales             #+#    #+#             */
/*   Updated: 2024/08/13 18:15:01 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dines(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	pthread_mutex_lock(&(sim->forks[philo->left_fork_id]));
	log_action(sim, philo->id, "has taken a fork");
	pthread_mutex_lock(&(sim->forks[philo->right_fork_id]));
	log_action(sim, philo->id, "has taken a fork");
	pthread_mutex_lock(&(sim->meal_check));
	log_action(sim, philo->id, "is eating");
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&(sim->meal_check));
	sleep_for(sim->time_to_eat, sim);
	(philo->meals_eaten)++;
	pthread_mutex_unlock(&(sim->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(sim->forks[philo->right_fork_id]));
}

void	*philo_thread(void *arg)
{
	int				i;
	t_philosopher	*philo;
	t_simulation	*sim;

	i = 0;
	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2)
		usleep(15000);
	while (!(sim->someone_died))
	{
		philo_dines(philo);
		if (sim->all_full)
			break ;
		log_action(sim, philo->id, "is sleeping");
		sleep_for(sim->time_to_sleep, sim);
		log_action(sim, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	cleanup_simulation(t_simulation *sim, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < sim->num_philos)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < sim->num_philos)
		pthread_mutex_destroy(&(sim->forks[i]));
	pthread_mutex_destroy(&(sim->write_lock));
}

void	check_death(t_simulation *sim, t_philosopher *philos)
{
	int	i;

	while (!(sim->all_full))
	{
		i = -1;
		while (++i < sim->num_philos && !(sim->someone_died))
		{
			pthread_mutex_lock(&(sim->meal_check));
			if (time_diff(philos[i].last_meal_time,
					get_current_time()) > sim->time_to_die)
			{
				log_action(sim, i, "died");
				sim->someone_died = 1;
			}
			pthread_mutex_unlock(&(sim->meal_check));
			usleep(100);
		}
		if (sim->someone_died)
			break ;
		i = 0;
		while (i < sim->num_philos && (sim->meals_required == -1
				|| philos[i].meals_eaten >= sim->meals_required))
			i++;
		if (i == sim->num_philos)
			sim->all_full = 1;
	}
}

int	launch_simulation(t_simulation *sim)
{
	int i;
	t_philosopher *philos;

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