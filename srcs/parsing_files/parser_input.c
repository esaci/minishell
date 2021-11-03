/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:30:33 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 21:30:34 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

t_token	*checker_next_token(t_token *toktmp)
{
	if (toktmp->type == CHAR_CHEVG || toktmp->type == CHAR_CHEVD)
		toktmp = parser_chevron(toktmp, toktmp->type);
	else if (toktmp->type == CHAR_GUILL || toktmp->type == CHAR_APO)
		toktmp = parser_in_between(toktmp, toktmp->type);
	else if (toktmp->type == CHAR_INUT)
		toktmp = parser_until_not(toktmp, toktmp->type, CHAR_SPACE);
	else if (toktmp->type == CHAR_TIRET
		||toktmp->type == CHAR_PIPE || toktmp->type == CHAR_DOLL)
		toktmp = parser_until_space(toktmp);
	else
		toktmp = toktmp->n_token;
	return (toktmp);
}

t_token	*parser_next_token(t_token *tok)
{
	t_token		*toktmp;

	toktmp = tok;
	while (toktmp && toktmp->type == CHAR_SPACE)
		toktmp = unlink_free_return(toktmp, 1);
	if (!toktmp)
		return (NULL);
	if (toktmp->type == CHAR_PIPE && !toktmp->n_token)
	{
		if (!g_exit_code[0])
			print_custom(
				"Minishell: syntax error near unexpected token `|'",
				2, 1, 1);
		*g_exit_code = 2;
	}
	if (!toktmp->n_token)
		return (NULL);
	toktmp = checker_next_token(toktmp);
	return (toktmp);
}

int	parser_lexer(t_lexer *lexer)
{
	t_token		*toktmp;
	int			count;

	count = 0;
	toktmp = lexer->tok;
	if (toktmp->type == CHAR_PIPE)
	{
		if (!g_exit_code[0])
			print_custom(
				"Minishell: syntax error near unexpected token `|'",
				2, 1, 1);
		*g_exit_code = 2;
	}
	while (toktmp)
	{
		toktmp->n_token = parser_next_token(toktmp);
		toktmp = toktmp->n_token;
		count++;
	}
	return (0);
}

t_lexer	*parser_input(t_lexer *lexer)
{
	init_lexer(lexer);
	if (!(*lexer->rl))
		return (lexer);
	if (!lexer->line_buffer)
		return (lexer);
	if (lexer_start(lexer, 0))
		return (NULL);
	if (parser_lexer(lexer))
		return (NULL);
	if (parser_output(lexer))
		return (NULL);
	return (lexer);
}
