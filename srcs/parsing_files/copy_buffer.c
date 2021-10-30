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

int	copy_buffer(char **buffu, t_token *tok)
{
	int		count;
	int		count2;
	char	c;
	char	*buff;
	int		count3;

	buff = *buffu;
	count = 0;
	count2 = 0;
	while (tok && tok->line[count2] == ' ')
		count2++;
	if (tok->type == CHAR_APO || tok->type == CHAR_GUILL)
	{
		count3 = arg_gestion(*buffu, tok);
		if (count3)
			return (count3);
		buff[count] = tok->line[count2];
		c = tok->line[count2];
		count++;
		count2++;
	}
	else if (tok->type == CHAR_DCHEVD || tok->type == CHAR_DCHEVG)
	{
		buff[count] = tok->line[count2];
		buff[count + 1] = tok->line[count2 + 1];
		buff[count + 2] = 0;
		return (count + 1);
	}
	else if (!tok->n_token)
		c = ' ';
	else if (tok->type == CHAR_CHEVD || tok->type == CHAR_CHEVG)
		c = tok->n_token->line[0];
	else if (tok->n_token->type == CHAR_INUT || tok->type == CHAR_TIRET
		|| tok->n_token->type == CHAR_ARG || tok->n_token->type == CHAR_DOLL)
		c = ' ';
	else if (tok->line[count] == tok->n_token->line[count2])
	{
		buff[count] = tok->line[count2];
		buff[++count] = 0;
		return (count);
	}
	else if (tok->type == CHAR_INUT)
	{
		count3 = arg_gestion(*buffu, tok);
		if (count3)
			return (count3);
		c = tok->n_token->line[0];
	}
	else
		c = tok->n_token->line[0];
	while (tok->line[count2] && tok->line[count2] != c)
	{
		if ((tok->type != CHAR_APO && tok->type
				!= CHAR_GUILL) && tok->line[count2] == ' ')
			break ;
		buff[count] = tok->line[count2];
		count++;
		count2++;
	}
	if ((tok->type == CHAR_APO || tok->type == CHAR_GUILL) && tok->line[count2])
	{
		buff[count++] = tok->line[count2];
		buff[count] = 0;
		remove_for_arg(buff);
		return (count);
	}
	buff[count] = 0;
	return (count);
}
