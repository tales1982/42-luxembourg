/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:04:45 by tales             #+#    #+#             */
/*   Updated: 2024/07/28 13:19:35 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\0')
	{
		while (reject[j] != '\0')
		{
			if(reject[j] == s[i])
                return(i);
            j++;
		}
        j = 0;
		i++;
	}
	return (i);
}
int	main(void)
{
	printf("%lu\n", ft_strcspn("test", "es"));
	printf("%lu\n", strcspn("test", "es"));
	printf("%lu\n", ft_strcspn("test", "f"));
	printf("%lu\n", strcspn("test", "f"));
}