/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:10:16 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:34:33 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mark_all_full(t_simulation *sim)
{
	pthread_mutex_lock(&(sim->meal_check));
	sim->all_full = 1;
	pthread_mutex_unlock(&(sim->meal_check));
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
	pthread_mutex_destroy(&(sim->meal_check));
}
