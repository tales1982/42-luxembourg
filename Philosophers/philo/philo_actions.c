/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:01:36 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:24:09 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeps_and_thinks(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	log_action(sim, philo->id, "is sleeping");
	sleep_for(sim->time_to_sleep, sim);
	pthread_mutex_lock(&(sim->meal_check));
	if (!sim->someone_died && !sim->all_full)
	{
		pthread_mutex_unlock(&(sim->meal_check));
		log_action(sim, philo->id, "is thinking");
	}
	else
		pthread_mutex_unlock(&(sim->meal_check));
}

void	philo_eats(t_philosopher *philo)
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
	philo->meals_eaten++;
	pthread_mutex_unlock(&(sim->meal_check));
	sleep_for(sim->time_to_eat, sim);
	pthread_mutex_unlock(&(sim->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(sim->forks[philo->right_fork_id]));
}
