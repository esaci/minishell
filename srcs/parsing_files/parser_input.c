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

t_token	*parser_chevron(t_token *t, TOKENTYPE type)
{
	t_token	*tmp;

	if (t->n_token->type == type)
	{
		t->type = t->type - 1;
		while (t->n_token->n_token && t->n_token->n_token->type == CHAR_SPACE)
			t->n_token->n_token = t->n_token->n_token->n_token;
		return(t->n_token->n_token);
	}
	else
	{
		tmp = t->n_token;
		while (tmp && tmp->type == CHAR_SPACE)
			tmp = tmp->n_token;
	}
	return (tmp);
}

t_token	*parser_in_between(t_token *t, TOKENTYPE type)
{
	t_token	*tmp;

	tmp = check_apo(t);
	if (tmp)
		return (tmp);
	tmp = t->n_token;
	while (tmp && tmp->type != type)
		tmp = tmp->n_token;
	if (!tmp)
		return (tmp);
	tmp = tmp->n_token;
	while (tmp && tmp->type == CHAR_SPACE)
		tmp = tmp->n_token;
	return (tmp);
}

t_token	*parser_until_not(t_token *t, TOKENTYPE type, TOKENTYPE type2)
{
	t_token	*tmp;

	tmp = t->n_token;
	while (tmp && tmp->type == type)
		tmp = tmp->n_token;
	while (tmp && tmp->type == type2)
		tmp = tmp->n_token;
	return (tmp);
}

t_token *parser_until_space(t_token *tok)
{
	t_token *tmp;

	tmp = tok->n_token;
	if (tok->type == CHAR_PIPE)
	{
		while (tmp && tmp->type == CHAR_SPACE)
			tmp = tmp->n_token;
		return (tmp);
	}
	while (tmp && tmp->type != CHAR_SPACE)
		tmp = tmp->n_token;
	if (!tmp)
		return (tmp);
	return (tmp->n_token);
}

t_token	*parser_next_token(t_token *tok)
{
	t_token		*toktmp;

	toktmp = tok;
	while (toktmp && toktmp->type == CHAR_SPACE)
		toktmp = toktmp->n_token;
	if (!toktmp)
		return (NULL);
	if (!toktmp->n_token)
		return (NULL);
	if (toktmp->type == CHAR_CHEVG || toktmp->type == CHAR_CHEVD)
		toktmp = parser_chevron(toktmp, toktmp->type);
	else if (toktmp->type == CHAR_GUILL || toktmp->type == CHAR_APO)
		toktmp = parser_in_between(toktmp, toktmp->type);
	else if (toktmp->type == CHAR_INUT)
		toktmp = parser_until_not(toktmp, toktmp->type, CHAR_SPACE);
	else if (toktmp->type == CHAR_TIRET || toktmp->type ==  CHAR_PIPE)
		toktmp = parser_until_space(toktmp);
	else
		toktmp = toktmp->n_token;
	return (toktmp);
}

int	parser_lexer(t_lexer *lexer)
{
	t_token		*toktmp;
	int			count;

	count = 0;
	toktmp = lexer->tok;
	while (toktmp)
	{
		toktmp->n_token = parser_next_token(toktmp);
		toktmp = toktmp->n_token;
		count++;
	}
	return (0);
}

t_lexer	*parser_input(t_lexer *lexer, char **envp)
{
	init_lexer(lexer, envp);
	if (lexer_start(lexer))
		return (NULL);
	if (parser_lexer(lexer))
		return (NULL);
	if (parser_output(lexer))
		return (NULL);
	return (lexer);
}
