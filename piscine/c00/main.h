/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:14:12 by tales             #+#    #+#             */
/*   Updated: 2024/08/22 21:20:34 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Cores e estilos de texto ANSI */
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

// ex00 ft_putchar
void	ft_putchar(char c);
// ex01 ft_print_alphabet
void	ft_print_alphabet(void);
void	ft_print_alphabet_v2(void);
// ex02 ft_print_reverse_alphabet
void	ft_print_reverse_alphabet(void);
void	ft_print_reverse_alphabet_v2(void);
// ex03 ft_print_numbers
void	ft_print_numbers(void);
// ex04 ft_is_negative
void	ft_is_negative(int n);
// ex05 ft_print_comb
void	ft_print_comb(void);
// ex06 ft_print_comb2
void	ft_print_comb2(void);
// ex07 ft_putnbr
void ft_putnbr(int nb);
#endif
