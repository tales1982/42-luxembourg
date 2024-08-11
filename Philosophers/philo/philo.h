/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:06:14 by tales             #+#    #+#             */
/*   Updated: 2024/08/11 22:09:54 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // Para pthread_create, pthread_detach, pthread_join,
//	pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
//	pthread_mutex_unlock
# include <stdio.h>    // Para printf
# include <stdlib.h>   // Para malloc, free
# include <string.h>   // Para memset
# include <sys/time.h> // Para gettimeofday
# include <unistd.h>   // Para usleep, write

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// Outras variáveis que possam ser necessárias
}					t_philosopher;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	// Outras variáveis para controlar a simulação
}					t_simulation;

#endif
