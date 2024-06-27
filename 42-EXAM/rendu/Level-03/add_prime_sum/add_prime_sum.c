/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:46:25 by tales             #+#    #+#             */
/*   Updated: 2024/06/27 21:47:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] >= 9 && str[i] <= 13)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
			i++;
		}
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sign);
}

int	is_prime(int num)
{
	int	i;

	i = 3;
	if (num <= 1)
		return (0); // Não é primo
	if (num == 2)
		return (1); // 2 é primo
	if (num % 2 == 0)
		return (0); // Não é primo
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0); // Não é primo
		i += 2;
	}
	return (1); // É primo
}
int main(void)
{
    int limit = 150; // Defina o limite até onde você quer verificar os números primos
    int i = 2;

    printf("Números primos até %d:\n", limit);
    while (i <= limit)
    {
        if (is_prime(i))
        {
            printf("%d ", i);
        }
        i++;
    }
    printf("\n");

    return 0;
}