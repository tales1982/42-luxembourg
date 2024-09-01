/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:05:22 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:24:32 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_dines(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	if (sim->num_philos == 1)
	{
		pthread_mutex_lock(&(sim->forks[philo->left_fork_id]));
		log_action(sim, philo->id, "has taken a fork");
		sleep_for(sim->time_to_die, sim);
		pthread_mutex_lock(&(sim->meal_check));
		if (time_diff(philo->last_meal_time,
				get_current_time()) > sim->time_to_die && !sim->someone_died)
		{
			log_action(sim, philo->id, "died");
			sim->someone_died = 1;
		}
		pthread_mutex_unlock(&(sim->meal_check));
		pthread_mutex_unlock(&(sim->forks[philo->left_fork_id]));
		return ;
	}
	philo_eats(philo);
}

void	*philo_thread(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&(sim->meal_check));
		if (sim->someone_died || sim->all_full)
		{
			pthread_mutex_unlock(&(sim->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(sim->meal_check));
		philo_dines(philo);
		philo_sleeps_and_thinks(philo);
	}
	return (NULL);
}
#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				ret;

	if (argc != 5 && argc != 6)
		return (handle_error(1));
	ret = init_simulation(&sim, argv);
	if (ret != 0)
		return (ret);
	if (launch_simulation(&sim))
		return (handle_error(3));
	return (0);
}

/*
	./philo 1 800 200 200 --> O filósofo não deveria comer e deveria morrer.
	./philo 5 800 200 200 --> Nenhum filósofo deveria morrer.
	./philo 5 800 200 200 7 --> Nenhum filósofo deve morrer e a simulação deve parar quando todos os filósofos tiverem comido pelo menos 7 vezes.
	./philo 4 410 200 200 --> Nenhum filósofo deveria morrer.
	./philo 4 310 200 100 --> Um filósofo deve morrer.
	Teste com 2 filósofos e verifique os diferentes tempos: uma morte adiada em mais de 10 ms é inaceitável.

 */