/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:06:14 by tales             #+#    #+#             */
/*   Updated: 2024/09/01 11:33:41 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct s_simulation;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	int					left_fork_id;
	int					right_fork_id;
	long long			last_meal_time;
	struct s_simulation	*sim;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_simulation
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_required;
	int					someone_died;
	int					all_full;
	long long			start_time;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		write_lock;
	t_philosopher		philos[250];
}						t_simulation;

/*
** ----- error_handler.c -----
*/

int						handle_error(int error_code);
// int						display_error(char *message);
// int						handle_error(int error_code);

/*
** ----- initialize.c -----
*/

int						init_simulation(t_simulation *sim, char **argv);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					log_action(t_simulation *sim, int id, char *message);
long long				get_current_time(void);
long long				time_diff(long long start, long long end);
void					sleep_for(long long time, t_simulation *sim);

/*
** ----- launch.c -----
*/

int						launch_simulation(t_simulation *sim);
void					cleanup_simulation(t_simulation *sim,
							t_philosopher *philos);
/*
** ----- start.c -----
*/

int						init_mutexes(t_simulation *sim);
int						init_simulation(t_simulation *sim, char **argv);
/*
** ----- philo_utils.c -----
*/
void					log_action(t_simulation *sim, int id, char *message);
long long				time_diff(long long start, long long end);
void					sleep_for(long long time, t_simulation *sim);
void					mark_all_full(t_simulation *sim);
void					philo_eats(t_philosopher *philo);

/*
** ----- simulation.c -----
*/
void					cleanup_simulation(t_simulation *sim,
							t_philosopher *philos);
void					check_death_and_full(t_simulation *sim,
							t_philosopher *philos);
int						launch_simulation(t_simulation *sim);
/*
** ----- philo.c -----
*/
void					philo_dines(t_philosopher *philo);
void					*philo_thread(void *arg);

void					philo_sleeps_and_thinks(t_philosopher *philo);
int						check_philo_death(t_simulation *sim,
							t_philosopher *philo, int i);
int						check_all_philos_full(t_simulation *sim,
							t_philosopher *philos);
#endif