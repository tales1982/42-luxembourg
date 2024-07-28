/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:55:00 by tales             #+#    #+#             */
/*   Updated: 2024/07/21 19:38:18 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void alpha_mirror(char *str)
{
    int i;
    char aux;
    

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] >= 65 && str[i] <= 90)
        {
            aux = 65 + 90 - str[i];
            ft_putchar(aux);
        }
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            aux = 'a' + 'z' - str[i];
            ft_putchar(aux);
        } 
        i++;
    }
    ft_putchar('\n');
}
int main(int ac, char **av)
{
    if(ac == 2)
    {
        alpha_mirror(av[1]);
    }
    ft_putchar('\n');

    return(0);
}