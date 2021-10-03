/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 14:39:30 by esaci             #+#    #+#             */
/*   Updated: 2021/10/01 14:39:31 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"


NODETYPE	is_any_chevron(t_token *t)
{
	if (t->type == CHAR_CHEVD)
		return (NODE_FILEOUT);
	if (t->type == CHAR_CHEVG)
		return (NODE_FILEIN);
	if (t->type == CHAR_DCHEVD)
		return (NODE_DFILEOUT);
	if (t->type == CHAR_DCHEVG)
		return (NODE_DFILEIN);
	return (NODE_ERROR);
}

int	is_arg(t_token *t)
{
	if (t->type == CHAR_INUT || t->type == CHAR_APO)
		return (1);
	if (t->type == CHAR_TIRET || t->type == CHAR_GUILL)
		return (1);
	return (0);
}

NODETYPE	is_any_command(t_lexer *l, t_token *t)
{
	char	*tmp;

	if (t->type != CHAR_INUT)
		return (NODE_ERROR);
	tmp = parse_is_command(l->buffer[get_buffer_count(l, t)] , l, 0);
	if (!access(tmp, F_OK))
	{
		l->buffer[get_buffer_count(l, t)] = tmp;
		fill_buffer(l);
		if (t->n_token && is_arg(t->n_token))
			t->n_token->type = CHAR_ARG;
		return (NODE_PATHCOM);
	}
	return (NODE_ERROR);
}


int	is_redirection(t_node *n2)
{
	if (!n2)
		return (0);
	if ((n2->type != NODE_DFILEIN || n2->type != NODE_PIPE))
		return (1);
	if (n2->type != NODE_DFILEOUT || n2->type == NODE_FILEIN)
		return (1);
	if (n2->type == NODE_FILEOUT)
		return (1);
	return (0);
}

int	get_buffer_count(t_lexer *l, t_token *t)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = l->tok;
	while (tmp && tmp != t)
	{
		tmp = tmp->n_token;
		count++;
	}
	return (count);
}

char	*first_false_command(t_token *t, t_lexer *l)
{
	t_token	*tmp;

	tmp = t;
	while (t && t->type != CHAR_INUT)
	{
		tmp = t;
		t = t->n_token;
	}
	if (!t)
		return ("");
	if (!is_any_chevron(tmp) && !is_arg(t))
		return (l->buffer[get_buffer_count(l, t)]);
	return (first_false_command(t->n_token, l));
}
