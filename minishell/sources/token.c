/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:58:10 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:31:27 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokent(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle || string[i] == D_QUOTE || string[i] == QUOTE)
			return (i);
		if (string[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

int	fix(t_tiny *tiny, char c, char *aux, int nbr)
{
	if (tiny->token.quote == 0 && (c == QUOTE || c == D_QUOTE))
		tiny->token.quote = c;
	else
	{
		if (tiny->token.quote == c)
			tiny->token.quote = 0;
		else
		{
			aux[nbr] = c;
			nbr++;
		}
	}
	return (nbr);
}

void	simple_quotes(t_tiny *tiny, char *in, int i, int c)
{
	char	*aux;

	tiny->token.quote = 0;
	aux = ft_strtrim(in, " ");
	tiny->has_flag = false;
	if (in[0] == '-' && in[1] == 'n')
	{
		tiny->has_flag = true;
		i += 2;
	}
	while (in[i] == ' ')
		i++;
	while (in[i])
	{
		c = fix(tiny, in[i], aux, c);
		i++;
	}
	aux[c] = '\0';
	free(tiny->token.to_print);
	tiny->token.to_print = aux;
}

void	tokenizer(t_tiny *tiny)
{
	t_token	*tk;

	tk = init_tk();
	tiny->token.quote = 0;
	tk->end = ft_strdup("");
	if (tiny->line)
	{
		while ((int)ft_strlen(tiny->line) > tk->i)
		{
			if (tiny->token.quote == 0 && (tiny->line[tk->i] == QUOTE))
				tiny->token.quote = tiny->line[tk->i];
			else
			{
				if (tiny->token.quote == tiny->line[tk->i])
					tiny->token.quote = 0;
				if (tiny->line[tk->i] == '~' && tiny->token.quote == 0)
					get_home_sign(tiny, tk);
				else if (tiny->line[tk->i] == '$' && tiny->token.quote == 0)
					get_dollar_sign(tiny, tk);
			}
			tk->len++;
			tk->i++;
		}
		finish_tokenizer(tiny, tk);
	}
}
