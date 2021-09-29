/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:07:57 by esaci             #+#    #+#             */
/*   Updated: 2021/09/29 07:08:02 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	poutput_strlen(t_token *tok)
{
	int	count;
	char	c;

	count = 0;
	if (!tok->n_token)
		c = '\0';
	else
		c = tok->n_token->line[0];
	while(tok->line[count] && tok->line[count] != c)
		count++;
	return (count);
}

int	copy_buffer(char *buff, t_token *tok)
{
	int	count;
	char	c;

	count = 0;
	if (!tok->n_token)
		c = '\0';
	else
		c = tok->n_token->line[0];
	while(tok->line[count] && tok->line[count] != c)
	{
		buff[count] = tok->line[count];
		count++;
	}
	buff[count] = 0;
	return (count);
}

int	malloc_buffer(t_lexer *lexer)
{
	int	count;
	t_token		*toktmp;

	toktmp = lexer->tok;
	count = 0;
	if (toktmp)
		count++;
	while (toktmp)
	{
		toktmp = toktmp->n_token;
		count++;
	}
	lexer->buffer = malloc(sizeof(char*) * (count + 1));
	if (!lexer->buffer)
		return (1);
	return (0);
}

int	fill_buffer(t_lexer *lexer)
{
	int			count;
	t_token		*toktmp;
	int			len;

	toktmp = lexer->tok;
	count = 0;
	while (toktmp)
	{
		len = poutput_strlen(toktmp);
		lexer->buffer[count] = malloc(sizeof(char) * (len + 1));
		if (!lexer->buffer[count])
			return (1);
		copy_buffer(lexer->buffer[count], toktmp);
		printf("Le token n°%d :|%s|\n", count, lexer->buffer[count]);
		toktmp = toktmp->n_token;
		count++;
	}
	return (0);
}

int	parser_output(t_lexer *lexer)
{
	if (malloc_buffer(lexer))
		return (1);
	if (fill_buffer(lexer))
		return (1);
	return (0);
}
