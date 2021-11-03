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

#include "../../lib/libmin.h"

int	add_path(char **ptr, t_token *t, t_lexer *l, char *err)
{
	if (!t || !t->n_token)
		*ptr = NULL;
	if (t->n_token && t->n_token->type == CHAR_INUT)
		*ptr = l->buffer[get_buffer_count(l, t->n_token)];
	else
	{
		*ptr = NULL;
		l->flagr[0] = 1;
		print_custom("Minishell: ", 2, 1, 0);
		print_custom(err, 2, 1, 0);
		l->last_exit = 2;
		return (print_custom(" syntax error", 2, 1, 1));
	}
	return (0);
}

int	tree_define_left(t_node *n, t_token *t, t_lexer *l)
{
	t_node	*left;

	if (n->type != NODE_PIPE)
		return (0);
	left = malloc(sizeof(t_node) * 2);
	if (!left)
		exit(small_free(l, NULL, NULL, 1));
	n->left = left;
	left->fd = NULL;
	left->archive_fd = NULL;
	left->str = NULL;
	if (search_command(left, t, l))
		return (1);
	if (tree_define_command(left, t, l))
		return (1);
	return (0);
}

int	tree_define_right(t_node *n, t_token *t, t_lexer *l)
{
	t_node	*right;

	if (n->type != NODE_PIPE)
		return (0);
	right = malloc(sizeof(t_node) * 2);
	if (!right)
		return (1);
	right->left = NULL;
	right->right = NULL;
	n->right = right;
	right->str = NULL;
	right->archive_fd = NULL;
	if (search_pipe(right, t, l))
		return (1);
	if (right->type != NODE_PIPE)
	{
		if (tree_define_command(right, t, l))
			return (1);
	}
	return (0);
}

int	small_definer(t_node *left, t_node *right, t_token *t, t_lexer *l)
{
	if (search_infile(left, t, l))
	{
		left->archive_fd = left->fd;
		return (1);
	}
	if (search_outfile(right, t, l))
	{
		left->archive_fd = left->fd;
		return (1);
	}
	left->archive_fd = left->fd;
	return (0);
}

int	tree_define_command(t_node *n, t_token *t, t_lexer *l)
{
	t_node	*right;
	t_node	*left;

	n->fd = NULL;
	if (n->type == NODE_PIPE)
		return (0);
	left = malloc(sizeof(t_node) * 2);
	if (!left)
		return (1);
	right = malloc(sizeof(t_node) * 2);
	if (!right)
		return (1);
	n->left = left;
	n->right = right;
	init_both_nodes(left, right);
	return (small_definer(left, right, t, l));
}
