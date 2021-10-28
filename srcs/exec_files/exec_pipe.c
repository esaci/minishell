	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:08:05 by esaci             #+#    #+#             */
/*   Updated: 2021/10/04 20:08:26 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

t_node	*exec_pipe(t_lexer *l, t_node *n, int count)
{
	int	exit_code;
	int	in;
	int	out;

	in = 0;
	l->pip->pid[count] = fork();
	if (l->pip->pid[count])
			close_archive(n->left->left->archive_fd);
	if (!l->pip->pid[count])
	{
		signal_default();
		if (n->left && n->left->str && (n->left->str + 1))
			in = new_menu(n->left->str[0], n->left->str + 1, l);
		if (in != -1)
		{
			in = l->last_exit;
			close_pipes(l, 1);
			small_free(l, NULL, NULL, 1);
			exit(in);
		}
		in = (count - 1) * 2;
		out = in + 3;
		if (count > 0)
			dup2(l->pip->ppd[in], STDIN_FILENO);
		dup2(l->pip->ppd[out], STDOUT_FILENO);
		exit_code = exec_com(l, n->left, count);
		exit(exit_code);
	}
	signal_wait_command();
	n = n->right;
	return (n);
}
