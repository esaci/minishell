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

	if (!lexer)
		return (mode);
	if (lexer->tok)
	{
		ltmp = lexer->tok;
		while (ltmp)
		{
			ltmp2 = ltmp->n_token;
			free(ltmp);
			ltmp = ltmp2;
		}
	}
	if (!lexer->buffer)
		return (mode);
	double_free(lexer->buffer);
	return (mode);
}

int	free_lexer_nodes(t_lexer *l, int mode)
{
	t_node	*n;
	t_node	*oldnode;

	if (!l)
		return (0);
	n = l->node;
	while (n)
	{
		if (n->left && n->left->type != NODE_FILEIN && n->left->type != NODE_DFILEIN)
		{
			if(n->left->left->fd)
				free(n->left->left->fd);
			free(n->left->left->str);
			free(n->left->left);
			free(n->left->right->str);
			free(n->left->right);
		}
		if (n->left)
		{
			if(n->left->fd)
				free(n->left->fd);
			free(n->left->str);
			free(n->left);
		}
		oldnode = n;
		n = n->right;
		free(oldnode->str);
		free(oldnode);
	}
	if (mode)
		init_lexer(l);
	return (0);
}

int	double_free(char **str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		free(str[count++]);
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