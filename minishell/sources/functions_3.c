/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:08:57 by luis-fif          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:43 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *s, char c)
{
	int	i;
	int	n_word;
	int	control;

	i = 0;
	control = 0;
	n_word = 0;
	while (s[0] != '\0' && s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			control = 1;
			n_word++;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (n_word);
}

char	*string(const char *s, int init, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc((end - init + 1) * sizeof(char));
	while (end > init)
	{
		string[i] = s[init];
		i++;
		init++;
	}
	string[i] = '\0';
	return (string);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		init_w;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (NULL);
	i = -1;
	j = 0;
	init_w = -1;
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && init_w < 0)
			init_w = i;
		else if ((s[i] == c || i == ft_strlen(s)) && init_w >= 0)
		{
			split[j++] = string(s, init_w, i);
			init_w = -1;
		}
	}
	split[j] = NULL;
	return (split);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0 && fd != 0)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
