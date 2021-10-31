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

int	nbr_apo_guill(t_token *t)
{
	int	count;
	int	count2;

	count = 0;
	while (t && (t->type == CHAR_APO
			|| t->type == CHAR_GUILL || t->type == CHAR_INUT))
	{
		if (t->type == CHAR_APO || t->type == CHAR_GUILL)
			count++;
		else
		{
			count2 = 0;
			while (t->n_token && ((t->line) + count2) != t->n_token->line)
			{
				if (((t->line) + count2)[0] == ' ')
					return (count * 2);
				count2++;
			}
		}
		t = t->n_token;
	}
	return (count * 2);
}

int	unlinker_arg(t_token *t, int count, int count4)
{
	if (count)
		t->n_token = unlink_free_return(t->n_token, 1);
	count = count4;
	if (t->line[count] != '\'' && t->line[count] != '\"'
		&& t->line[count] != '<' && t->line[count] != '>'
		&& t->line[count] != ' ' && t->line[count] != '|')
		t->n_token = unlink_free_return(t->n_token, 1);
	else if (t->n_token && (t->line[count] == '\''
			|| t->line[count] == '\"') && t->n_token->type == CHAR_INUT)
		t->n_token = unlink_free_return(t->n_token, 1);
	return (count);
}

int	len_new_buff(t_token *t, int count, int count4, char c)
{
	while (t && t->line && t->line[count])
	{
		c = t->line[count];
		if (c == '<' || c == '>' || c == ' ' || c == '|')
			break ;
		if (c == '\'' || c == '\"')
		{
			count4 = count + 1;
			while (t && t->line && t->line[count4] && t->line[count4] != c)
				count4++;
			if (!t || !t->line || !t->line[count4])
				return (count4);
			count4++;
			count = unlinker_arg(t, count, count4);
		}
		else
			count++;
	}
	return (count);
}

int	arg_gestion2(t_token *t, char *buff, int count3, int count)
{
	int		len;
	char	c;

	len = len_new_buff(t, 0, 0, 0);
	count = count3;
	c = 0;
	while (count < len && t->line && t->line[count])
	{
		if (t->line[count] == '\'' || t->line[count] == '\"')
		{
			if (!c)
				c = t->line[count];
			else if (c == t->line[count])
				c = 0;
			else
				buff[count3++] = t->line[count];
		}
		else
			buff[count3++] = t->line[count];
		count++;
	}
	buff[count3] = 0;
	return (1);
}

int	arg_gestion(char *buff, t_token *t)
{
	int		count3;

	if (t->n_token && t->n_token->type
		!= CHAR_APO && t->n_token->type != CHAR_GUILL)
	{
		if (t->type != CHAR_APO && t->type != CHAR_GUILL)
			return (0);
	}
	count3 = 0;
	while (t->type == CHAR_INUT && (t->line + count3) != t->n_token->line)
	{
		if ((t->line + count3)[0] == ' ')
		{
			buff[count3] = 0;
			return (1);
		}
		buff[count3] = (t->line + count3)[0];
		count3++;
	}
	t->type = CHAR_INUT;
	return (arg_gestion2(t, buff, count3, 0));
}
