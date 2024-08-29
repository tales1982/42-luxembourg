/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:45:31 by tales             #+#    #+#             */
/*   Updated: 2024/08/29 21:28:59 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(result * sign));
}

long long	get_current_time(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return ((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000));
}

long long	time_diff(long long start, long long end)
{
	return (end - start);
}
void sleep_for(long long time, t_simulation *sim)
{
    long long start_time = get_current_time();
    while (!(sim->someone_died))
    {
        if (time_diff(start_time, get_current_time()) >= time)
            break;
        usleep(500);  // Verificações mais frequentes
    }

}
void log_action(t_simulation *sim, int id, char *message)
{
    pthread_mutex_lock(&(sim->write_lock));
    if (!sim->someone_died)
    {
        printf("%3lld %d %s\n", get_current_time() - sim->start_time, id + 1, message);
    }
    pthread_mutex_unlock(&(sim->write_lock));
}



