/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:13:00 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 17:36:25 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

enum NODETYPE	tree_check_type(t_lexer *l, t_token *t)
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
		return (is_any_command(l, t, t));
	return (NODE_ARG);
}

t_node	*gestion_error(t_node **n)
{
	(*n) = malloc(sizeof(t_node) * 2);
	if (!*n)
		return (NULL);
	(*n)->left = NULL;
	(*n)->right = NULL;
	(*n)->str = NULL;
	(*n)->type = NODE_ERROR;
	return ((*n));
}

t_node	*tree_parser_node(t_node **n)
{
	t_node	*tmp;

	if (!(*n))
		return (gestion_error(n));
	tmp = (*n)->right;
	while (tmp->left && (tmp->left->type == NODE_PATHCOM
			|| tmp->left->type == NODE_NOCOM))
	{
		if (!tmp->right)
		{
			print_custom("Erreur Parsing node", 1, 0, 1);
			return (NULL);
		}
		tmp = tmp->right;
		if (tmp->right && (tmp->right->type == NODE_FILEOUT
				|| tmp->right->type == NODE_DFILEOUT))
			return (NULL);
	}
	return (tmp);
}

t_token	*tree_init_node(t_lexer *l, t_token *t, t_node **node)
{
	t_node		*n;

	n = tree_parser_node(node);
	if (!n)
		return (NULL);
	if (search_pipe(n, t, l))
		exit(small_free(l, NULL, NULL, 1));
	if (tree_define_command(n, t, l))
		exit(small_free(l, NULL, NULL, 1));
	if (tree_define_left(n, t, l))
		exit(small_free(l, NULL, NULL, 1));
	if (tree_define_right(n, t, l))
		exit(small_free(l, NULL, NULL, 1));
	while (t && (t->type != CHAR_PIPE))
		t = t->n_token;
	if (t)
		t = t->n_token;
	return (t);
}

t_node	*tree_input(t_lexer *lexer)
{
	t_token	*t;
	t_node	**node;

	if (!lexer->rl[0])
		return (NULL);
	node = &(lexer->node);
	t = lexer->tok;
	while (t)
		t = tree_init_node(lexer, t, node);
	return (lexer->node);
}
