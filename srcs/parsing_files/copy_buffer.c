/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 00:51:23 by elias             #+#    #+#             */
/*   Updated: 2021/10/31 00:51:25 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

char	next_char_end2(t_token *tok, char *c, int fd[2], char **buffu)
{
	int	count3;

	if (!tok->n_token)
		*c = ' ';
	else if (tok->type == CHAR_CHEVD || tok->type == CHAR_CHEVG)
		*c = tok->n_token->line[0];
	else if (tok->n_token->type == CHAR_INUT || tok->type == CHAR_TIRET
		|| tok->n_token->type == CHAR_ARG || tok->n_token->type == CHAR_DOLL)
		*c = ' ';
	else if (tok->line[fd[0]] == tok->n_token->line[fd[1]])
	{
		(*buffu)[fd[0]] = tok->line[fd[1]];
		(*buffu)[++fd[0]] = 0;
		return (fd[0]);
	}
	else if (tok->type == CHAR_INUT)
	{
		count3 = arg_gestion(*buffu, tok);
		if (count3)
			return (count3);
		*c = tok->n_token->line[0];
	}
	else
		*c = tok->n_token->line[0];
	return (-1);
}

char	next_char_end(t_token *tok, char *c, int fd[2], char **buffu)
{
	int	count3;

	while (tok && tok->line[fd[1]] == ' ')
		fd[1]++;
	if (tok->type == CHAR_APO || tok->type == CHAR_GUILL)
	{
		count3 = arg_gestion(*buffu, tok);
		if (count3)
			return (count3);
		(*buffu)[fd[0]] = tok->line[fd[1]];
		*c = tok->line[fd[1]];
		fd[0]++;
		fd[1]++;
	}
	else if (tok->type == CHAR_DCHEVD || tok->type == CHAR_DCHEVG)
	{
		(*buffu)[fd[0]] = tok->line[fd[1]];
		(*buffu)[fd[0] + 1] = tok->line[fd[1] + 1];
		(*buffu)[fd[0] + 2] = 0;
		return (fd[0] + 1);
	}
	else
		return (next_char_end2(tok, c, fd, buffu));
	return (-1);
}

int	copy_buffer(char **buffu, t_token *tok, int fd[2])
{
	char	c;
	int		count3;

	fd[0] = 0;
	fd[1] = 0;
	count3 = next_char_end(tok, &c, fd, buffu);
	if (count3 != -1)
		return (count3);
	while (tok->line[fd[1]] && tok->line[fd[1]] != c)
	{
		if ((tok->type != CHAR_APO && tok->type
				!= CHAR_GUILL) && tok->line[fd[1]] == ' ')
			break ;
		(*buffu)[fd[0]++] = tok->line[fd[1]++];
	}
	if ((tok->type == CHAR_APO || tok->type == CHAR_GUILL) && tok->line[fd[1]])
	{
		(*buffu)[fd[0]++] = tok->line[fd[1]];
		(*buffu)[fd[0]] = 0;
		remove_for_arg((*buffu));
		return (fd[0]);
	}
	(*buffu)[fd[0]] = 0;
	return (fd[0]);
}
