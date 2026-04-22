/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:33:41 by tales             #+#    #+#             */
/*   Updated: 2024/08/13 18:11:03 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_error(int error_code)
{
	if (error_code == 1)
		printf("Error: Invalid argument\n");
	else if (error_code == 2)
		printf("Error: Mutex initialization failed\n");
	else if (error_code == 3)
		printf("Error: Thread creation failed\n");
	else if (error_code == 4)
		printf("Error: Memory allocation failed\n");
	return (error_code);
}
