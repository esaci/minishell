/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:13:00 by esaci             #+#    #+#             */
/*   Updated: 2021/09/29 12:13:01 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

NODETYPE	ti_check_type(t_lexer *l, t_token *t)
{
	if (t->type == CHAR_PIPE)
		return (NODE_PIPE);
	if (is_any_chevron(t))
	{
		if (!t->n_token)
			return (NODE_ERROR);
		if (t->n_token->type != CHAR_INUT)
			return (NODE_ERROR);
		t->n_token->type = CHAR_ARG;
		return (is_any_chevron(t));
	}
	if (t->type == CHAR_INUT)
		return (is_any_command(l, t));
	return (NODE_ARG);
}

int	tree_init_node(t_lexer *l)
{
	t_token		*t;

	if (!l->tok)
		return (0);
	t = l->tok;
	n = malloc(sizeof(t_node) * 2);
	if (!n)
		return (1);
	while (t && t->type != CHAR_PIPE)
		t = t->n_token;
	if (!t)
		tree_state1(l->tok);
	tree_state2(l->tok);
	
	return (0);
}

t_node	*tree_input(t_lexer *lexer)
{
	if (tree_init_node(lexer))
		return (NULL);
	return (lexer->node);
}
