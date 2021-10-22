/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:35:35 by elias             #+#    #+#             */
/*   Updated: 2021/10/22 19:35:39 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int		nbr_apo_guill(t_token *t)
{
	int	count;

	count = 1;
	while (t && (t->type == CHAR_APO || t->type == CHAR_GUILL))
	{
		t = t->n_token;
		count++;
	}
	return (count * 2);
}

int		len_new_buff(t_token *t)
{
	int		count;
	int		count3;
	char	c;

	count3 = nbr_apo_guill(t->n_token);
	count = 0;
	while (t->line[count])
	{
		c = t->line[count];
		if (c == '<' || c == '>' || c == ' ' || c == '|')
			break;
		if (count3 && (c == '\'' || c == '\"'))
		{
			t->n_token = unlink_free_return(t->n_token, 1);
			count3--;
			count++;
			while (t->line[count] && t->line[count] != c)
				count++;
		}
		count++;
	}
	return (count);
}

int		arg_gestion(char **ptr, t_token *t)
{
	int		count;
	int		len;
	int		count2;
	char	*buff;
	int		count3;

	buff = *ptr;
	if (t->n_token->type != CHAR_APO && t->n_token->type != CHAR_GUILL)
		return (0);
	count2 = nbr_apo_guill(t->n_token);
	if (t->type != CHAR_INUT)
		count2 = count2 + 2;
	count3 = 0;
	while (t->line != t->n_token->line)
	{
		buff[count3++] = t->line[0];
		t->line++;
	}
	len = len_new_buff(t);
	count = 0;
	while(count < len)
	{
		if (count2 < 1 || (t->line[count] != '\'' && t->line[count] != '\"'))
			buff[count3++] = t->line[count];
		else
			count2--;
		count++;
	}
	buff[count3] = 0;
	return (count);
}
