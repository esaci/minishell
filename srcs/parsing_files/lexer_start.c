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

#include "../../lib/libmin.h"

TOKENTYPE	lexer_check_type2(t_token *tok, char *oldstr)
{
	if (tok->line[0] ==  '$')
		return (CHAR_DOLL);
	if (tok->line[0] ==  '\?')
		return (CHAR_INTER);
	if (tok->line[0] ==  ' ')
		return (CHAR_SPACE);
	if (tok->line[0] ==  '-' && (oldstr[0] == CHAR_SPACE))
		return (CHAR_TIRET);
	if (tok->line[0] ==  '\0')
		return (CHAR_Z);
	return (CHAR_INUT);
}

TOKENTYPE	lexer_check_type(t_token *tok, char *oldstr)
{
	if (tok->line[0] ==  '|')
		return (CHAR_PIPE);
	if (tok->line[0] ==  '\"')
	{
		if (!check_apo(tok, 0))
			return (CHAR_GUILL);
		return (CHAR_INUT);
	}
	if (tok->line[0] ==  '\'')
	{
		if (!check_apo(tok, 0))
			return (CHAR_APO);
		return (CHAR_INUT);
	}
	if (tok->line[0] ==  '<')
		return (CHAR_CHEVG);
	if (tok->line[0] ==  '>')
		return (CHAR_CHEVD);
	return (lexer_check_type2(tok, oldstr));
}

int	init_lexer(t_lexer *lexer, char **envp)
{
	lexer->envp = envp;
	lexer->len = 0;
	lexer->tok = NULL;
	lexer->buffer = NULL;
	lexer->node = NULL;
	lexer->pip = NULL;
	return (0);
}

t_token	*lexer_token(char *str, char *oldstr)
{
	t_token		*toktmp;
	int			count;

	toktmp = malloc(sizeof(t_token) * 2);
	if (!(toktmp))
		return (NULL);
	count = 0;
	while (str && str[count] == ' ')
		count++;
	(toktmp)->line = str + count;
	(toktmp)->type = lexer_check_type(toktmp, oldstr);
	(toktmp)->n_token = NULL;
	return (toktmp);
}

int	lexer_start(t_lexer *lexer)
{
	int			count;
	t_token		**toktmp;

	if (!rl_line_buffer)
		return (1);
	lexer->tok = lexer_token(rl_line_buffer, rl_line_buffer);
	count = 1;
	toktmp = &(lexer->tok->n_token);
	while(rl_line_buffer[count])
	{
		(*toktmp) = lexer_token(rl_line_buffer + count, rl_line_buffer + count - 1);
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
