/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:04:59 by tales             #+#    #+#             */
/*   Updated: 2024/07/24 20:37:43 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	main(void)
{
	printf("Original vs Clone: <%d> <%d>", strcmp("hello World", "hello world"),
		ft_strcmp("hello World", "hello world"));
	printf("\nOriginal vs Clone: <%d> <%d>", strcmp("hello World", ""),
		ft_strcmp("hello World", ""));
}
