/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:07:37 by tales             #+#    #+#             */
/*   Updated: 2024/07/21 13:39:12 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void rotone(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if((str[i] >= 'a' && str[i] <= 'y') || (str[i] >= 'A' && str[i] <= 'Y'))
        {
            ft_putchar(str[i] + 1);
        }
        else if(str[i] == 'z')
            ft_putchar('a');
        else if(str[i] == 'Z')
            ft_putchar('A');
        else
            ft_putchar(str[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        rotone(argv[1]);
    }
    else
    {
        ft_putchar('\n');
    }
    return 0;
}