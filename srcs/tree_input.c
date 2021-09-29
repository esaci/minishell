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
	t_token *tmp;

	if (t->type == CHAR_PIPE)
		return (NODE_PIPE);
	if (t->type == CHAR_CHEVD || t->type == CHAR_CHEVG)
	{
		if (!t->n_token)
			return (NODE_ERROR);
		if (t->n_token->type != CHAR_INUT)
			return (NODE_ERROR);
		tmp = t->n_token;
		t->n_token = tmp->n_token;
		free(tmp);
		fill_buffer(l);
		return (NODE_FILEOUT);
	}
	if (t->type == CHAR_CHEVG)
		return (NODE_ERROR);
	return (NODE_ARG);
}

int	tree_init_node(t_lexer *l, t_node **node)
{
	int			count;
	t_token		*t;
	t_node		*n;
	t_node		*n2;

	if (!l->tok)
		return (0);
	t = l->tok;
	n2 = *node;
	count = 0;
	while (t)
	{
		n = malloc(sizeof(t_node) * 2);
		if (!n)
			return (1);
		n->str = l->buffer[count];
		n->type = ti_check_type(l, t);
		if (count)
		{
			n2->after = n;
			n->before = n2;
			n->after = NULL;
			n2 = n;
		}
		else
		{
			*node = n;
			n->before = NULL;
			n->after = NULL;
			n2 = n;
		}
		t = t->n_token;
		count++;
	}
	return (0);
}

t_node	*tree_input(t_lexer *lexer, t_node **node)
{
	if (tree_init_node(lexer, node))
		return (NULL);
	return (*node);
}
