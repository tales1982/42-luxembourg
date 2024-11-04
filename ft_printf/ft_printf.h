/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:36:46 by tlima-de          #+#    #+#             */
/*   Updated: 2024/03/08 19:37:24 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>

int	ft_printf(const char *input, ...);
int	print_pointer(unsigned long value, int asc);
int	print_unsigned(unsigned int nb);
int	print_string(char *s);
int	print_int(int n);
int	print_char(char c);
int	print_hex(unsigned int value, int asc);

#endif
