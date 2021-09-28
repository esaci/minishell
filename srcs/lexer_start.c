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

int	init_lexer(t_lexer *lexer)
{
	lexer->len = 0;
	lexer->tok = NULL;
	/* lexer->tok = malloc(sizeof(t_token*) * 2); */
	/* if (!lexer->tok)
		return (1);
	lexer->tok->line = rl_line_buffer;
	lexer->tok->type = lexer_check_type(lexer->tok);
	lexer->tok->n_token = NULL; */
	return (0);
}

int	lexer_token(t_lexer *lexer, char *str)
{
	t_token		**toktmp;

	toktmp = &(lexer->tok);
	while (*toktmp)
		*toktmp = (*toktmp)->n_token;
	*toktmp = malloc(sizeof(t_token) * 2);
	if (!(*toktmp))
		return (0);
	(*toktmp)->line = str;
	(*toktmp)->type = lexer_check_type(*toktmp);
	(*toktmp)->n_token = NULL;
	return (1);
	printf("cque je viens de modif %d vs %d - %s\n", (*toktmp)->type, lexer->tok->type, str);
}

int	lexer_start(t_lexer *lexer)
{
	int	count;
	int	count2;

	count = 0;
	while(rl_line_buffer[count])
	{
		count2 = lexer_token(lexer, rl_line_buffer + count);
		lexer->len++;
		if (!count2)
		{
			free_lexer_tokens(lexer);
			return (1);
		}
		count += count2;
	}
	return (0);
}
