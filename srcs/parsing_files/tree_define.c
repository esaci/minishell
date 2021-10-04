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
/* print_custom(*ptr, 1, 1,1); */
void	add_path(char **ptr, t_token *t, t_lexer *l)
{
	char *tmp;

	if (!t || !t->n_token)
	{
		tmp = malloc(sizeof(char) * 1);
		if (!tmp)
		{
			*ptr = NULL;
			return ;
		}
		tmp[0] = '\0';
		*ptr = tmp;
	}
	if (t->n_token->type == CHAR_INUT)
		*ptr = l->buffer[get_buffer_count(l, t->n_token)];
	else
		{
			tmp = malloc(sizeof(char) * 1);
			if (!tmp)
			{
				*ptr = NULL;
				return ;
			}
			tmp[0] = '\0';
			*ptr = tmp;
		}
}

int	tree_define_left(t_node *n, t_token *t, t_lexer *l)
{
	t_node	*left;

	if (n->type != NODE_PIPE)
		return (0);
	left = malloc(sizeof(t_node) * 2);
	if (!left)
		return (1);
	n->left = left;
	left->str = NULL;
	if (search_command(left, t, l))
		return (1);
	if (tree_define_command(left, t, l))
		return (1);
	return (0);
}

int	tree_define_right(t_node *n, t_token *t, t_lexer *l)
{
	t_node *right;

	if (n->type != NODE_PIPE)
		return (0);
	right = malloc(sizeof(t_node) * 2);
	if (!right)
		return (1);
	right->left = NULL;
	right->right = NULL;
	n->right = right;
	right->str = NULL;
	if (search_pipe(right, t, l))
		return (1);
	if (right->type != NODE_PIPE)
	{
		if (tree_define_command(right, t, l))
			return (1);
	}
	return (0);
}


int	tree_define_command(t_node *n, t_token *t, t_lexer *l)
{
	t_node *right;
	t_node *left;

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
	if (search_infile(left, t, l))
		return (1);
	if (search_outfile(right, t, l))
		return (1);
	return (0);
}
