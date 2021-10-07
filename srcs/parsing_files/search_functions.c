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

#include "../../lib/libmin.h"

int	search_node_str_com(t_node *n, t_token *t, t_lexer *l)
{
	int		count;
	t_token *tmp;

	if (n->type != NODE_NOCOM && n->type != NODE_PATHCOM)
		return (0);
	count = 1;
	tmp = t;
	while (t && t->type != CHAR_PIPE)
	{
		if ((t->type == CHAR_INUT && !is_any_chevron(tmp)) || is_arg(t))
		{
			n->str[count] = l->buffer[get_buffer_count(l, t)];
			count++;
		}
		tmp = t;
		t = t->n_token;
	}
	n->str[count] = NULL;
	return (0);
	return(l->buffer[0][0]);
}

int	search_command(t_node *n, t_token *t, t_lexer *l)
{
	t_token *tmp;
	t_token	*tmp2;
	int		count;

	tmp = t;
	tmp2 = t;
	while (t && ((t->type != CHAR_INUT || is_any_chevron(tmp)) || (!is_arg(t))))
	{
		tmp = t;
		t = t->n_token;
	}
	if (!t)
	{
		n->type = NODE_NOCOM;
		no_com_fill(n, l, tmp2);
		return (0);
	}
	count = is_any_command(l, t, tmp);
	if (count)
		n->type = NODE_PATHCOM;
	else
		n->type = NODE_NOCOM;
	count = nbr_com(l, tmp2);
	n->str = malloc(sizeof(char*) * (count + 3));
	if (!n->str)
		return (1);
	n->str[count] = NULL;
	n->str[0] = l->buffer[get_buffer_count(l, t)];
	if (search_node_str_com(n, t->n_token, l))
		return (1);
	return (0);
}

int	search_pipe(t_node *n, t_token *t, t_lexer *l)
{
	t_token *tmp;

	tmp = t;
	while (t && t->type != CHAR_PIPE)
		t = t->n_token;
	if (t)
	{
		n->type = NODE_PIPE;
		n->str = malloc(sizeof(char*) * 1);
		if (!n->str)
			return (1);
		n->str[0] = 0;
	}
	else
	{
		if (search_command(n, tmp, l))
			return (1);
	}
	return (0);
}

int	search_infile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;
	int	count2;
	t_token	*tmp;

	n->left = NULL;
	n->right = NULL;
	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVG || tmp->type == CHAR_DCHEVG)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * ((count*2) + 2));
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
			n->type = NODE_FILEIN;
			if (t->type == CHAR_DCHEVG)
				n->type = NODE_DFILEIN;
			add_path(&n->str[count++], t, l);
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
	t_token	*tmp;

	n->left = NULL;
	n->right = NULL;
	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVD || tmp->type == CHAR_DCHEVD)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * ((count*2) + 2));
	if (!n->str)
		return (1);
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_CHEVD || t->type == CHAR_DCHEVD)
		{
			n->str[count] = l->buffer[get_buffer_count(l, t)];
			count++;
			n->type = NODE_FILEOUT;
			if (t->type == CHAR_DCHEVD)
				n->type = NODE_DFILEOUT;
			add_path(&n->str[count++], t, l);
		}
		t = t->n_token;
	}
	n->str[count] = NULL;
	if (!n->str[0])
	{
		n->type = NODE_FILEOUT;
		n->str[0] = "/dev/stdout";
		n->str[1] = 0;
		n->right = NULL;
		n->left = NULL;
	}
	return (0);
}

/* if (!is_any_chevron(tmp2) && !is_arg(t))
			{
				n->str[count2] = l->buffer[count];
				count2++;
			} */
