/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:34:28 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 00:43:04 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	search_chevg(t_node *n, t_token *t, t_lexer *l, int i)
{
	int	j;

	j = get_buffer_count(l, t);
	n->str[i] = l->buffer[j];
	i++;
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
	if (add_path(&n->str[i], t, l, n->str[i - 1]))
		return (-1);
	i++;
	return (0);
}

int	search_chevd(t_node *n, t_token *t, t_lexer *l, int i)
{
	n->str[i] = l->buffer[get_buffer_count(l, t)];
	i++;
	n->type = NODE_FILEOUT;
	if (t->type == CHAR_DCHEVD)
		n->type = NODE_DFILEOUT;
	if (add_path(&n->str[i], t, l, n->str[i - 1]))
		return (-1);
	i++;
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
		close(*g_exit_code);
		*g_exit_code = 130;
	}
}