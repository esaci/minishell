/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:34:28 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/03 17:17:13 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	search_chevg(t_node *n, t_token *t, t_lexer *l, int *count)
{
	int	j;

	j = get_buffer_count(l, t);
	n->str[*count] = l->buffer[j];
	(*count)++;
	n->type = NODE_FILEIN;
	if (t->type == CHAR_DCHEVG)
	{
		if (t->n_token && t->n_token->type == CHAR_INUT)
			n->fd = join_int(n->fd,
					l->buffer[get_buffer_count(l, t->n_token)], l);
		else
		{
			free(n->fd);
			n->fd = NULL;
		}
		n->type = NODE_DFILEIN;
	}
	if (add_path(&n->str[*count], t, l, n->str[*count - 1]))
		return (-1);
	(*count)++;
	return (0);
}

int	search_chevd(t_node *n, t_token *t, t_lexer *l, int *count)
{
	n->str[*count] = l->buffer[get_buffer_count(l, t)];
	(*count)++;
	n->type = NODE_FILEOUT;
	if (t->type == CHAR_DCHEVD)
		n->type = NODE_DFILEOUT;
	if (add_path(&n->str[*count], t, l, n->str[*count - 1]))
		return (-1);
	(*count)++;
	return (0);
}

void	free_loop_fd_in(t_node *n)
{
	int	count;

	if (!n->str[0])
	{
		if (n->fd)
		{
			count = 0;
			while (n->fd[count] != -1)
				close(n->fd[count]);
			free(n->fd);
		}
		n->type = NODE_FILEIN;
		n->str[0] = "/dev/stdin";
		n->str[1] = 0;
	}
}

void	free_loop_fd_out(t_node *n)
{
	if (!n->str[0])
	{
		n->type = NODE_FILEOUT;
		n->str[0] = "/dev/stdout";
		n->str[1] = 0;
	}
}

void	infile_exit_code(void)
{
	if (*g_exit_code > 2)
	{
		signal_wait_input();
		dup2(*g_exit_code, STDIN_FILENO);
		if (*g_exit_code > -1)
			close(*g_exit_code);
		*g_exit_code = 130;
	}
}
