/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:39:47 by esaci             #+#    #+#             */
/*   Updated: 2021/10/02 20:39:48 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	search_node_str_com(t_node *n, t_token *t, t_lexer *l)
{
	int	count;

	count = get_buffer_count(l, t);
	n->str = malloc(sizeof(char*) * (3));
	if (!n->str)
		return (1);
	n->str[2] = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (is_any_command(l, t))
			n->str[0] = l->buffer[count];
		if (t->type == CHAR_ARG)
			n->str[1] = l->buffer[count];
		count++;
		t = t->n_token;
	}
	return (0);
}

int	search_command(t_node *n, t_token *t, t_lexer *l)
{
	NODETYPE	tmp;

	tmp = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_INUT)
			tmp = is_any_command(l, t);
		if (tmp)
			break ;
		t = t->n_token;
	}
	if (tmp)
		n->type = NODE_PATHCOM;
	else
		n->type = NODE_NOCOM;
	if (n->str)
		return (0);
	if (search_node_str_com(n, t, l))
		return (1);
	return (0);
}

int	search_pipe(t_node *n, t_token *t, t_lexer *l)
{
	while (t && t->type != CHAR_PIPE)
		t = t->n_token;
	if (t)
	{
		n->type = NODE_PIPE;
		n->str = NULL;
	}
	else
	{
		if (search_command(n, t, l))
			return (1);
	}
	return (0);
}

int	search_infile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;
	int	count2;
	t_token	*tmp;

	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVG || tmp->type == CHAR_DCHEVG)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * (count + 2));
	if (!n->str)
		return (1);
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_CHEVG || t->type == CHAR_DCHEVG)
		{
			count2 = get_buffer_count(l, t);
			n->str[count] = l->buffer[count2];
			count++;
		}
		t = t->n_token;
	}
	n->str[count] = NULL;
	if (!n->str[0])
	{
		n->type = NODE_FILEIN;
		n->str[0] = "/dev/stdin";
		n->str[1] = 0;
	}
	return (0);
}

int	search_outfile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;
	int	count2;
	t_token	*tmp;

	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVD || tmp->type == CHAR_DCHEVD)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * (count + 2));
	if (!n->str)
		return (1);
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_CHEVD || t->type == CHAR_DCHEVD)
		{
			count2 = get_buffer_count(l, t);
			n->str[count] = l->buffer[count2];
			count++;
		}
		t = t->n_token;
	}
	n->str[count] = NULL;
	if (!n->str[0])
	{
		n->type = NODE_FILEOUT;
		n->str[0] = "/dev/stdout";
		n->str[1] = 0;
	}
	return (0);
}
