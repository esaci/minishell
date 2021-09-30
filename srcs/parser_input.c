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

t_token	*parser_chevron(t_token *t, TOKENTYPE type)
{
	t_token	*tmp;

	if (t->n_token->type == type)
		return(t->n_token->n_token);
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

	tmp = t->n_token;
	while (tmp && tmp->type != type)
		tmp = tmp->n_token;
	if (!tmp)
		return (tmp);
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
	while (tmp && tmp->type != CHAR_SPACE)
		tmp = tmp->n_token;
	return (tmp);
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
	else if (toktmp->type == CHAR_TIRET)
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

t_lexer	*parser_input(t_lexer *lexer)
{
	init_lexer(lexer);
	if (lexer_start(lexer))
		return (NULL);
	if (parser_lexer(lexer))
		return (NULL);
	if (parser_output(lexer)) // check ici
		return (NULL);
	return (lexer);
}
