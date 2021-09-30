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
	while(tok && tok->line[count] == ' ')
		count++;
	if (!tok->n_token)
		c = '\0';
	else if (tok->n_token->type == CHAR_INUT || tok->n_token->type == CHAR_TIRET)
		c = ' ';
	else if ((tok->type == CHAR_APO || tok->type == CHAR_GUILL) && tok->line[count])
	{
		c = tok->line[count];
		count++;
	}
	else
		c = tok->n_token->line[count];
	while(tok->line[count] && tok->line[count] != c)
		count++;
	return (count);
}

int	copy_buffer(char *buff, t_token *tok)
{
	int	count;
	int	count2;
	char	c;

	count = 0;
	count2 = 0;
	while(tok && tok->line[count2] == ' ')
		count2++;
	if (tok->type == CHAR_APO || tok->type == CHAR_GUILL)
	{
		buff[count] = tok->line[count2];
		c = tok->line[count2];
		count++;
		count2++;
	}
	else if (tok->type == CHAR_DCHEVD || tok->type == CHAR_DCHEVG)
	{
		buff[count] = tok->line[count2];
		buff[count + 1] = tok->line[count2 + 1];
		buff[count + 2] = 0;
		return (count + 1);
	}
	else if (!tok->n_token)
		c = ' ';
	else if (tok->type == CHAR_CHEVD || tok->type == CHAR_CHEVG)
		c = tok->n_token->line[0];
	else if (tok->n_token->type == CHAR_INUT || tok->type == CHAR_TIRET)
		c = ' ';
	else if (tok->line[count] == tok->n_token->line[count2])
	{
		buff[count] = tok->line[count2];
		buff[++count] = 0;
		return (count);
	}
	else
		c = tok->n_token->line[0];
	while(tok->line[count2] && tok->line[count2] != c)
	{
		if ((tok->type != CHAR_APO && tok->type != CHAR_GUILL) && tok->line[count2] == ' ')
			break;
		buff[count] = tok->line[count2];
		count++;
		count2++;
	}
	if ((tok->type == CHAR_APO || tok->type == CHAR_GUILL) && tok->line[count2])
	{
		buff[count] = tok->line[count2];
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
		lexer->buffer[count] = malloc(sizeof(char) * (len + 2));
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
