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

	tmp = parse_is_command(t->line , l, 0);
	write(1, "C UNE COMMANDE ? : ", 19);
	write(1, t->line, ft_strlen(t->line));
	write(1, " vs : ", 6);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	if (!access(tmp, F_OK))
	{
		write(1, "C UNE COMMANDE !\n", 17);
		t->line = tmp;
		fill_buffer(l);
		if (t->n_token && is_arg(t->n_token))
			t->n_token->type = CHAR_ARG;
		return (NODE_PATHCOM);
	}
	return (NODE_ERROR);
}
