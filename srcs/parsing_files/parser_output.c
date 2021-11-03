/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:07:57 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 02:59:20 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	poutput_strlen(t_token *tok)
{
	int		count;
	char	c;

	c = '\0';
	count = 0;
	while (tok->line[count] && tok->line[count] != c)
		count++;
	return (count + 10);
}

int	malloc_buffer(t_lexer *lexer)
{
	int		count;
	int		count2;
	t_token	*toktmp;

	toktmp = lexer->tok;
	count = 0;
	if (toktmp)
		count++;
	while (toktmp)
	{
		toktmp = toktmp->n_token;
		count++;
	}
	lexer->buffer = malloc(sizeof(char *) * (count + 100));
	if (!lexer->buffer)
		exit(small_free(lexer, NULL, NULL, 1));
	count2 = 0;
	while (count2 < (count + 2))
		lexer->buffer[count2++] = NULL;
	return (0);
}

int	fill_buffer(t_lexer *lexer)
{
	int			count;
	t_token		*toktmp;
	int			len;
	int			fd[2];

	toktmp = lexer->tok;
	count = 0;
	while (toktmp)
	{
		len = poutput_strlen(toktmp);
		lexer->buffer[count] = malloc(sizeof(char) * (len + 2));
		if (!lexer->buffer[count])
			exit(small_free(lexer, NULL, NULL, 1));
		copy_buffer(&(lexer->buffer[count]), toktmp, fd);
		toktmp = toktmp->n_token;
		count++;
	}
	return (0);
}

int	parser_output(t_lexer *lexer)
{
	if (!(*lexer->rl))
		return (0);
	if (malloc_buffer(lexer))
		return (1);
	if (fill_buffer(lexer))
		return (1);
	return (0);
}
