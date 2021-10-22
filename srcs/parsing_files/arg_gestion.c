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
	count3 = 2;
	count = 0;
	while (t && t->line && t->line[count])
	{
		c = t->line[count];
		if (c == '<' || c == '>' || c == ' ' || c == '|')
			break;
		if (count3 && (c == '\'' || c == '\"'))
		{
			t->n_token = unlink_free_return(t->n_token, 2);
			count3--;
			count++;
			while (t && t->line && t->line[count] && t->line[count] != c)
				count++;
			if (!t || !t->line || !t->line[count])
				return (count);
			count++;
		}
		else
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
	if (t->n_token && t->n_token->type != CHAR_APO && t->n_token->type != CHAR_GUILL)
	{
		if (t->type != CHAR_APO && t->type != CHAR_GUILL)
			return (0);
	}
	count2 = nbr_apo_guill(t);
	count3 = 0;
	while (t->type == CHAR_INUT && (t->line + count3) != t->n_token->line)
	{
		if ((t->line + count3)[0] == ' ')
		{
			buff[count3] = 0;
			return (count3 + 1);
		}
		buff[count3] = (t->line + count3)[0];
		count3++;
	}
	len = len_new_buff(t);
	t->type = CHAR_INUT;
	count = count3;
	while(count < len && t->line && t->line[count])
	{
		if (count2 < 1 || (t->line[count] != '\'' && t->line[count] != '\"'))
			buff[count3++] = t->line[count];
		else
			count2--;
		count++;
	}
	buff[count3] = 0;
	print_custom(buff, 1, 1, 1);
	return (count + 1);
}
