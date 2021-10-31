/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 04:31:23 by elias             #+#    #+#             */
/*   Updated: 2021/10/31 04:31:26 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	*join_int(int *fd, char *str, t_lexer *l)
{
	int	*ptr;
	int	count;

	if (!fd)
	{
		ptr = malloc(sizeof(int) * 2);
		ptr[0] = -1;
		ptr[1] = -1;
		exec_in_heredoc(str, ptr, l);
		return (ptr);
	}
	count = 0;
	while (fd && fd[count] != -1)
		count++;
	ptr = malloc(sizeof(int) * (count + 2));
	count = 0;
	while (fd && fd[count] != -1)
	{
		ptr[count] = fd[count];
		count++;
	}
	exec_in_heredoc(str, ptr + count, l);
	ptr[count + 1] = -1;
	free(fd);
	return (ptr);
}

int	search_node_str_com(t_node *n, t_token *t, t_lexer *l)
{
	int		count;
	t_token	*tmp;

	if (n->type != NODE_NOCOM && n->type != NODE_PATHCOM)
		return (0);
	count = 1;
	tmp = t;
	while (t && t->type != CHAR_PIPE)
	{
		if ((t->type == CHAR_INUT && !is_any_chevron(tmp)) || (is_arg(t) == 1))
		{
			n->str[count] = l->buffer[get_buffer_count(l, t)];
			count++;
		}
		tmp = t;
		t = t->n_token;
	}
	n->str[count] = NULL;
	return (0);
}
