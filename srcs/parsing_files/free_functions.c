/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:12:06 by esaci             #+#    #+#             */
/*   Updated: 2021/09/27 19:12:08 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	free_lexer_tokens(t_lexer *lexer, int mode)
{
	t_token		*ltmp;
	t_token		*ltmp2;
	int			count;

	(void)mode;
	count = 0;
	if (!lexer)
		return (count);
	if (lexer->tok)
	{
		ltmp = lexer->tok;
		while (ltmp)
		{
			ltmp2 = ltmp->n_token;
			free(ltmp);
			ltmp = ltmp2;
			count++;
		}
	}
	if (!lexer->buffer)
		return (count);
	double_free(lexer->buffer);
	return (count);
}

int	free_lexer_nodes(t_lexer *l)
{
	t_node	*n;
	t_node	*oldnode;

	n = l->node;
	while (n)
	{
		oldnode = n;
		if (n->type == NODE_FILEOUT || !n->left)
		{
			free(n->str);
			free(n);
			break ;
		}
		if (n->left->type != NODE_FILEIN && n->left->type != NODE_DFILEIN)
		{
			free(n->left->left->str);
			free(n->left->left);
			free(n->left->right->str);
			free(n->left->right);
		}
		free(n->left->str);
		free(n->left);
		if (n->right && (n->right->type == NODE_FILEOUT || n->right->type == NODE_DFILEOUT))
		{
			free(n->right->str);
			free(n->right);
			break;
		}
		n = n->right;
		free(oldnode->str);
		free(oldnode);
	}
	init_lexer(l, NULL);
	return (0);
}

int	double_free(char **str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	while (count >= 0)
		free(str[count--]);
	free(str);
	return (0);
}

t_token	*unlink_free_return(t_token *t, int skip)
{
	t_token *oldt;
	int		count;

	if (!t)
		return (t);
	count = 0;
	while (t && count < skip)
	{
		oldt = t;
		t = t->n_token;
		free(oldt);
		count++;
	}
	return (t);
}