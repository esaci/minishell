/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:03:51 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/04 00:38:55 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	close_fd_pipe(int fd)
{
	if (fd > -1)
		close(fd);
}

void	exec_pipe_split(t_lexer *l, t_node *n, int count, int fdin)
{
	int	in;
	int	exit_code;

	if (!l->pip->pid[count])
	{
		if (n->left && n->left->str && (n->left->str + 1))
			in = new_menu(n->left->str[0], n->left->str + 1, l);
		if (in != -1)
		{
			in = l->last_exit;
			close_pipes(l, 1);
			small_free(l, NULL, NULL, 1);
			exit(in);
		}
		if (count > 0)
			dup2(fdin, STDIN_FILENO);
		close_fd_pipe(fdin);
		dup2(l->pip->ppd[1], STDOUT_FILENO);
		close_fd_pipe(l->pip->ppd[1]);
		exit_code = exec_com(l, n->left, count);
		exit(exit_code);
	}
}

t_node	*exec_pipe(t_lexer *l, t_node *n, int count, int *fdin)
{
	*fdin = dup(l->pip->ppd[0]);
	if (l->pip->ppd[0] > -1)
		close(l->pip->ppd[0]);
	if (l->pip->ppd[1] > -1)
		close(l->pip->ppd[1]);
	pipe(l->pip->ppd);
	l->pip->pid[count] = fork();
	if (l->pip->pid[count])
	{
		if (n && n->left && n->left->left && n->left->left->archive_fd)
			close_archive(n->left->left->archive_fd);
	}
	exec_pipe_split(l, n, count, *fdin);
	signal_wait_command();
	if (*fdin > -1)
		close(*fdin);
	n = n->right;
	return (n);
}
