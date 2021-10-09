/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:23:40 by esaci             #+#    #+#             */
/*   Updated: 2021/10/03 22:23:41 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	nbr_com(t_lexer *l, t_token *t)
{
	int		count;

	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		count++;
		t = t->n_token;
	}
	return (count);
	return (l->tok->line[0]);
}

void	no_com_fill(t_node *n, t_lexer *l, t_token *t)
{
	t_token *tmp;
	int		count;
	t_token *tmp2;

	if (n->type == NODE_PIPE)
		return ;
	tmp2 = t;
	n->type = NODE_NOCOM;
	tmp = t;
	count = 0;
	while(t)
	{
		if (t->type == CHAR_INUT && !is_any_chevron(tmp))
			count++;
		tmp = t;
		t = t->n_token;
	}
	n->str = malloc(sizeof(char*) * (count + 3));
	if (!n->str)
		return;
	tmp = tmp2;
	count = 0;
	while (tmp2)
	{
		if (tmp2->type == CHAR_INUT && !is_any_chevron(tmp))
			n->str[count++] = l->buffer[get_buffer_count(l, tmp2)];
		tmp = tmp2;
		tmp2 = tmp2->n_token;
	}
	n->str[count] = NULL;
}

t_token	*check_apo(t_token *t)
{
	char	c;
	int		count;

	if (t->line[0] != '\'' && t->line[0] != '\"')
		return (NULL);
	c = t->line[0];
	count = 1;
	while (t->line[count] && t->line[count] != c)
		count++;
	if (!t->line[count])
	{
		t->type = CHAR_INUT;
		return (parser_next_token(t));
	}
	return (NULL);
}