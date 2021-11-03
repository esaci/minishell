/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 04:31:23 by elias             #+#    #+#             */
/*   Updated: 2021/11/03 02:58:58 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	*no_fd(char *str, t_lexer *l)
{
	int	*ptr;

	ptr = malloc(sizeof(int) * 2);
	if (!ptr)
		return (NULL);
	ptr[0] = -1;
	ptr[1] = -1;
	exec_in_heredoc(str, ptr, l);
	return (ptr);
}

int	*join_int(int *fd, char *str, t_lexer *l)
{
	int	*ptr;
	int	count;

	if (!fd)
		return (no_fd(str, l));
	count = 0;
	while (fd && fd[count] != -1)
		count++;
	ptr = malloc(sizeof(int) * (count + 2));
	if (!ptr)
		return (NULL);
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

int	malloc_node_redir(t_node *n, t_token *t,
	enum TOKENTYPE r1, enum TOKENTYPE r2)
{
	t_token	*tmp;
	int		count;

	n->left = NULL;
	n->right = NULL;
	n->fd = NULL;
	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == r1 || tmp->type == r2)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char *) * ((count * 2) + 2));
	if (!n->str)
		return (1);
	return (0);
}
