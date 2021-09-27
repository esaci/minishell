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

#include "../lib/libmin.h"

t_token	*parser_chevrong(t_token *t)
{
	t_token	*tmp;

	if (t->n_token->type == CHAR_CHEVG)
		return(t->n_token->n_token);
	else
	{
		tmp = t->n_token;
		while (tmp && tmp->type != CHAR_INUT)
			tmp = tmp->n_token;
		if (!tmp || tmp->type != )

	}
	return (tmp);
}

t_token	*parser_next_token(t_token *tok)
{
	t_token		*toktmp;
	TOKENTYPE	tmp;
	TOKENTYPE	tmp2;

	tmp = CHAR_INUT;
	tmp2 = CHAR_TMP;
	if (!tok)
		return (NULL);
	if (!tok->n_token)
		return (NULL);
	toktmp = tok->n_token;
	while (toktmp->type == CHAR_SPACE && toktmp)
		toktmp = toktmp->n_token;
	if (!toktmp)
		return (NULL);
	if (tok->n_token && tok->type == CHAR_CHEVG)
		toktmp = parser_chevrong(tok);
	else if (tok->type == CHAR_CHEVD)
	{
		if (tok->n_token && tok->n_token->type == CHAR_CHEVD)
			return  (tok->n_token->n_token);
		return (tok->n_token);
	}
	return (toktmp);
}

int	parser_lexer(t_lexer *lexer)
{
	t_token		**toktmp;

	toktmp = &lexer->tok;
	while (*toktmp)
	{
		(*toktmp)->n_token = parser_next_token(*toktmp);
		toktmp = &(*toktmp)->n_token;
	}
	return (0);
}

t_lexer	*parser_input(t_lexer *lexer)
{
	init_lexer(lexer);
	if (lexer_start(lexer))
		return (NULL);
	if (parser_lexer(lexer))
		return (NULL);
	return (lexer);
}
