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
	else if (tok->n_token->type == CHAR_INUT || tok->n_token->type == CHAR_TIRET)
		c = ' ';
	else if(tok->type == CHAR_APO || tok->type == CHAR_GUILL)
		c = tok->line[count++];
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
	else if (tok->n_token->type == CHAR_INUT || tok->n_token->type == CHAR_TIRET)
		c = ' ';
	else if (tok->type == CHAR_DCHEVD || tok->type == CHAR_DCHEVG)
	{
		buff[count++] = tok->line[0];
		buff[count++] = tok->line[1];
		return (count);
	}
	else if(tok->type == CHAR_APO || tok->type == CHAR_GUILL)
	{
		buff[count++] = tok->line[0];
		c = tok->line[0];
	}
	else if (tok->line[0] == tok->n_token->line[0])
	{
		buff[0] = tok->line[0];
		buff[1] = 0;
		return (1);
	}
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
	lexer->buffer = malloc(sizeof(char*) * (count + 2));
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
