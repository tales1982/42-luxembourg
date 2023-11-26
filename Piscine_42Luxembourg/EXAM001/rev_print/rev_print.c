/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ######.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmarti <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:19 by tales             #+#    #+#             */
/*   Updated: 2022/09/25 16:58:31 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>

char	*ft_rev_print(char *str);
int		length(char *str);

/*
int	main(void)
{

	char	str[] = "vida loca";
	ft_rev_print(str);

}
*/

int	length(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}

char	*ft_rev_print(char *str)
{
	int	i;

	i = length(str);
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
	return (str);
}
