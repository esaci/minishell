/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:38:45 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 17:36:05 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

enum TOKENTYPE	lexer_check_type2(t_token *tok, char *oldstr)
{
	if (tok->line[0] == '$')
		return (CHAR_INUT);
	if (tok->line[0] == ' ')
		return (CHAR_SPACE);
	if (tok->line[0] == '-' && (oldstr[0] == CHAR_SPACE))
		return (CHAR_TIRET);
	if (tok->line[0] == '\0')
		return (CHAR_Z);
	return (CHAR_INUT);
}

enum TOKENTYPE	lexer_check_type(t_token *tok, char *oldstr)
{
	if (tok->line[0] == '|')
		return (CHAR_PIPE);
	if (tok->line[0] == '\"')
	{
		if (!check_apo(tok, 0))
			return (CHAR_GUILL);
		return (CHAR_INUT);
	}
	if (tok->line[0] == '\'')
	{
		if (!check_apo(tok, 0))
			return (CHAR_APO);
		return (CHAR_INUT);
	}
	if (tok->line[0] == '<')
		return (CHAR_CHEVG);
	if (tok->line[0] == '>')
		return (CHAR_CHEVD);
	return (lexer_check_type2(tok, oldstr));
}

int	init_lexer(t_lexer *lexer)
{
	if (!lexer)
		return (1);
	lexer->len = 0;
	lexer->tok = NULL;
	lexer->buffer = NULL;
	lexer->node = NULL;
	lexer->pip = NULL;
	lexer->c_tok = NULL;
	lexer->flagr[0] = 0;
	g_exit_code = lexer->flagr;
	if (!(*lexer->rl))
		return (0);
	init_path_pwd(lexer, 1);
	init_line_buffer(lexer, 0, 0, 0);
	return (0);
}

t_token	*lexer_token(char *str, char *oldstr)
{
	t_token		*toktmp;

	toktmp = malloc(sizeof(t_token) * 2);
	if (!(toktmp))
		return (NULL);
	(toktmp)->line = str;
	(toktmp)->type = lexer_check_type(toktmp, oldstr);
	(toktmp)->n_token = NULL;
	return (toktmp);
}

int	lexer_start(t_lexer *lexer, int mode)
{
	t_token		**toktmp;

	while (lexer->line_buffer && lexer->line_buffer[mode] == ' ')
		mode++;
	lexer->tok = lexer_token(lexer->line_buffer + mode,
			lexer->line_buffer + mode);
	if (!lexer->tok)
		return (1);
	toktmp = &(lexer->tok->n_token);
	if (!lexer->line_buffer[mode])
		return (0);
	mode++;
	while (lexer->line_buffer[mode])
	{
		(*toktmp) = lexer_token(lexer->line_buffer + mode,
				lexer->line_buffer + mode - 1);
		if (!(*toktmp))
			return (free_lexer_tokens(lexer, 1));
		lexer->len++;
		toktmp = &((*toktmp)->n_token);
		mode++;
	}
	return (0);
}
