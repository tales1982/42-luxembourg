/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:51:13 by tales             #+#    #+#             */
/*   Updated: 2024/07/14 09:58:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}
void ft_putstr(char *str)
{
    int i;
    
    i = 0;
    while(str[i] != '\0')
    {
        ft_putchar(str[i]);
        i++;
    }    
}

void first_word(char *str)
{
    int i;
    
    i = 0;
    while(str[i] <= 32 && str[i] != '\0')
        i++;
    while(str[i] > 32)
    {
        ft_putchar(str[i]);
        i++;
    }
        
}

int main(int ac, char **av)
{
    int i;

    i = 0;
    if(ac == 2)
        first_word(av[1]);
    ft_putchar('\n');
    return(0);
}