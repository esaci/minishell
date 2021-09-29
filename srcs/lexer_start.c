/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:38:45 by esaci             #+#    #+#             */
/*   Updated: 2021/09/27 18:39:01 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

TOKENTYPE	lexer_check_type2(t_token *tok)
{
	if (tok->line[0] ==  '-')
		return (CHAR_TIRET);
	if (tok->line[0] ==  '&')
		return (CHAR_ET);
	if (tok->line[0] ==  '\0')
		return (CHAR_Z);
	if (tok->line[0] ==  ';')
		return (CHAR_PVIR);
	if (tok->line[0] ==  '\\')
		return (CHAR_SLAHV);
	if (tok->line[0] ==  '\t')
		return (CHAR_TAB);
	if (tok->line[0] ==  '\n')
		return (CHAR_Z);
	return (CHAR_INUT);
}

TOKENTYPE	lexer_check_type(t_token *tok)
{
	if (tok->line[0] ==  '|')
		return (CHAR_PIPE);
	if (tok->line[0] ==  '\"')
		return (CHAR_GUILL);
	if (tok->line[0] ==  '\'')
		return (CHAR_APO);
	if (tok->line[0] ==  '<')
		return (CHAR_CHEVG);
	if (tok->line[0] ==  '>')
		return (CHAR_CHEVD);
	if (tok->line[0] ==  '$')
		return (CHAR_DOLL);
	if (tok->line[0] ==  '\?')
		return (CHAR_INTER);
	if (tok->line[0] ==  '(')
		return (CHAR_PARO);
	if (tok->line[0] ==  ')')
		return (CHAR_PARF);
	if (tok->line[0] ==  '.')
		return (CHAR_POINT);
	if (tok->line[0] ==  ' ')
		return (CHAR_SPACE);
	return (lexer_check_type2(tok));
}

int	init_lexer(t_lexer *lexer)
{
	lexer->len = 0;
	lexer->tok = NULL;
	lexer->buffer = NULL;
	return (0);
}

t_token	*lexer_token(char *str)
{
	t_token		*toktmp;

	toktmp = malloc(sizeof(t_token) * 2);
	if (!(toktmp))
		return (NULL);
	(toktmp)->line = str;
	(toktmp)->type = lexer_check_type(toktmp);
	(toktmp)->n_token = NULL;
	return (toktmp);
}

int	lexer_start(t_lexer *lexer)
{
	int			count;
	t_token		**toktmp;

	if (!rl_line_buffer)
		return (1);
	lexer->tok = lexer_token(rl_line_buffer);
	count = 1;
	toktmp = &(lexer->tok->n_token);
	while(rl_line_buffer[count])
	{
		(*toktmp) = lexer_token(rl_line_buffer + count);
		lexer->len++;
		if (!(*toktmp))
		{
			free_lexer_tokens(lexer);
			return (1);
		}
		toktmp = &((*toktmp)->n_token);
		count++;
	}
	return (0);
}
