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

int	tree_init_node(t_lexer *l, t_node **node)
{
	int			count;
	t_token		*t;
	t_node		*n;
	t_node		*n2;

	count = 0;
	if (!l->tok)
		return (0);
	t = l->tok;
	n = *node;
	n2 = *node;
	n->before = NULL;
	while (t)
	{
		n = malloc(sizeof(t_node) * 2);
		if (!n)
			return (1);
		n->str = buffer[count];
		n->type = ti_check_type(t);
		if (count)
		{
			n2->after = n;
			n2 = n;
		}
		t = t->n_token;
		count++;
}

t_node	*parser_next_token(t_lexer *lexer, t_node **node)
{
	if (tree_init_node(lexer, node))
		return (NULL);
}
