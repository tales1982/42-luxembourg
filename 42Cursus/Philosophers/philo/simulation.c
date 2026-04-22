/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:00:49 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 12:38:49 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death_and_full(t_simulation *sim, t_philosopher *philos)
{
	int	i;
	int	philos_full;

	while (!sim->someone_died)
	{
		i = -1;
		philos_full = 0;
		while (++i < sim->num_philos && !sim->someone_died)
		{
			pthread_mutex_lock(&(sim->meal_check));
			if (time_diff(philos[i].last_meal_time,
					get_current_time()) > sim->time_to_die)
			{
				log_action(sim, i, "died");
				sim->someone_died = 1;
			}
			if (sim->meals_required > 0
				&& philos[i].meals_eaten >= sim->meals_required)
				philos_full++;
			pthread_mutex_unlock(&(sim->meal_check));
		}
		if (philos_full == sim->num_philos)
			mark_all_full(sim);
		usleep(1000);
	}
}
