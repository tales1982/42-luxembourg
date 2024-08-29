/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:44:05 by tales             #+#    #+#             */
/*   Updated: 2024/08/29 21:27:28 by tales            ###   ########.fr       */
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

void	philo_dines(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	// Caso especial para um único filósofo
	if (sim->num_philos == 1)
	{
		pthread_mutex_lock(&(sim->forks[philo->left_fork_id]));
		log_action(sim, philo->id, "has taken a fork");
		sleep_for(sim->time_to_die, sim);
		// Verifique se o filósofo ainda não foi marcado como morto e imprima "died"
		pthread_mutex_lock(&(sim->meal_check));
		if (!sim->someone_died)
		{
			log_action(sim, philo->id, "died");
			sim->someone_died = 1;
		}
		pthread_mutex_unlock(&(sim->meal_check));
		pthread_mutex_unlock(&(sim->forks[philo->left_fork_id]));
		return ;
	}
	// Processo normal para múltiplos filósofos
	pthread_mutex_lock(&(sim->meal_check));
	if (time_diff(philo->last_meal_time, get_current_time()) > sim->time_to_die)
	{
		log_action(sim, philo->id, "died");
		sim->someone_died = 1;
		pthread_mutex_unlock(&(sim->meal_check));
		return ;
	}
	pthread_mutex_unlock(&(sim->meal_check));
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
		if (sim->someone_died)
			break ;
		log_action(sim, philo->id, "is sleeping");
		sleep_for(sim->time_to_sleep, sim);
		if (sim->someone_died)
			break ;
		pthread_mutex_lock(&(sim->meal_check));
		if (time_diff(philo->last_meal_time,
				get_current_time()) > sim->time_to_die)
		{
			log_action(sim, philo->id, "died");
			sim->someone_died = 1;
			pthread_mutex_unlock(&(sim->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(sim->meal_check));
		log_action(sim, philo->id, "is thinking");
		pthread_mutex_lock(&(sim->meal_check));
		if (time_diff(philo->last_meal_time,
				get_current_time()) > sim->time_to_die)
		{
			log_action(sim, philo->id, "died");
			sim->someone_died = 1;
			pthread_mutex_unlock(&(sim->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(sim->meal_check));
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
	pthread_mutex_destroy(&(sim->meal_check));
}

void check_death(t_simulation *sim, t_philosopher *philos)
{
    int i;

    while (!sim->all_full)
    {
        i = -1;
        while (++i < sim->num_philos && !sim->someone_died)
        {
            pthread_mutex_lock(&(sim->meal_check));
            if (time_diff(philos[i].last_meal_time, get_current_time()) > sim->time_to_die)
            {
                log_action(sim, i, "died");
                sim->someone_died = 1;
            }
            pthread_mutex_unlock(&(sim->meal_check));
        }

        if (sim->someone_died)
            break;

        // Verificação para ver se todos os filósofos comeram o suficiente
        i = 0;
        while (i < sim->num_philos && (philos[i].meals_eaten >= sim->meals_required))
            i++;

        if (i == sim->num_philos)
        {
            sim->all_full = 1;
        }

        usleep(1000);  // Pequeno delay para evitar uso excessivo de CPU
    }
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
