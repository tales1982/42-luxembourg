/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:14:31 by tales             #+#    #+#             */
/*   Updated: 2024/07/31 19:22:57 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	max(int *tab, unsigned int len)
{
	int	aux;
	int	i;

	i = 1;
	if (len == 0)
		return (0);
	aux = tab[0];
	while (i < len)
	{
		if (aux < tab[i])
			aux = tab[i];
		i++;
	}
	return (aux);
}
/*
int main() {
    int array1[] = {1, 3, 7, 0, -2, 5};
    int array2[] = {-10, -3, -1, -20, -50};
    int array3[] = {};
    unsigned int len1 = sizeof(array1) / sizeof(array1[0]);
    unsigned int len2 = sizeof(array2) / sizeof(array2[0]);
    unsigned int len3 = 0;

    printf("Maior valor no array1: %d\n", max(array1, len1));
    printf("Maior valor no array2: %d\n", max(array2, len2));
    printf("Maior valor no array3: %d\n", max(array3, len3));

    return 0;
}
*/
