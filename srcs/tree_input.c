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
	int			count;
	t_token		*t;
	t_node		*n;
	t_node		*n2;

	if (!l->tok)
		return (0);
	t = l->tok;
	count = 0;
	while (t)
	{
		n = malloc(sizeof(t_node) * 2);
		if (!n)
			return (1);
		n->type = ti_check_type(l, t);
		if (count)
		{
			n2->right = n;
			n->left = n2;
			n->right = NULL;
			n2 = n;
		}
		else
		{
			l->node = n;
			n->left = NULL;
			n->right = NULL;
			n2 = n;
		}
		t = t->n_token;
		count++;
	}
	return (0);
}

t_node	*tree_input(t_lexer *lexer)
{
	if (tree_init_node(lexer))
		return (NULL);
	return (lexer->node);
}
