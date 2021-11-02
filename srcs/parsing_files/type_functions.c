/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 14:39:30 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 17:35:12 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

enum NODETYPE	is_any_chevron(t_token *t)
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
	if (t->type == CHAR_INUT)
		return (2);
	if (t->type == CHAR_APO)
		return (1);
	if (t->type == CHAR_TIRET || t->type == CHAR_GUILL)
		return (1);
	return (0);
}

enum NODETYPE	is_any_command(t_lexer *l, t_token *t, t_token *oldt)
{
	char	*tmp;

	if (t->type != CHAR_INUT)
		return (NODE_ERROR);
	tmp = parse_is_command(l->buffer[get_buffer_count(l, t)], l, 0, 0);
	if (!access(tmp, F_OK) && !is_any_chevron(oldt))
	{
		free(tmp);
		return (NODE_PATHCOM);
	}
	free(tmp);
	return (NODE_ERROR);
}

int	is_redirection(t_node *n2)
{
	if (!n2)
		return (0);
	if ((n2->type == NODE_DFILEIN || n2->type == NODE_PIPE))
		return (1);
	if (n2->type == NODE_DFILEOUT || n2->type == NODE_FILEIN)
		return (1);
	if (n2->type == NODE_FILEOUT)
		return (1);
	return (0);
}

int	get_buffer_count(t_lexer *l, t_token *t)
{
	t_token	*tmp;
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
