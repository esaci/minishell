/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_define.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:56:39 by esaci             #+#    #+#             */
/*   Updated: 2021/10/02 21:56:41 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	tree_define_left(t_node *n, t_token *t, t_lexer *l)
{
	t_node	*left;

	if (n->left)
		return (0);
	left = malloc(sizeof(t_node) * 2);
	if (!left)
		return (1);
	left->left = NULL;
	left->right = NULL;
	n->left = left;
	left->str = NULL;
	if (n->type == NODE_PIPE)
	{
		left->str = NULL;
		if (search_command(left, t, l))
			return (1);
		return (0);
	}
	if (search_infile(left, t, l))
		return (1);
	return (0);
}

int	tree_define_right(t_node *n, t_token *t, t_lexer *l)
{
	t_node *right;

	if (n->right)
		return (0);
	right = malloc(sizeof(t_node) * 2);
	if (!right)
		return (1);
	right->left = NULL;
	right->right = NULL;
	n->right = right;
	right->str = NULL;
	if (n->type == NODE_PIPE)
	{
		right->str = NULL;
		if (search_pipe(right, t, l))
			return (1);
		return (0);
	}
	return (0);
}
