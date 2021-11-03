/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:50:15 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 17:14:21 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	ultime_close_archive(t_lexer *l)
{
	t_node	*n;

	n = l->node;
	while (n && n->type == NODE_PIPE)
	{
		if (n && n->left && n->left->left && n->left->left->archive_fd)
			close_archive(n->left->left->archive_fd);
		n = n->right;
	}
	if (n)
	{
		if (n && n->left && n->left->archive_fd)
			close_archive(n->left->archive_fd);
	}
}

int	exec_input_split(t_lexer *l, t_node *n)
{
	int	count;
	int	count2;
	int	fdin;

	count = 0;
	fdin = 0;
	while (n && n->type == NODE_PIPE)
		n = exec_pipe(l, n, count++, &fdin);
	if (exec_com(l, n, count++))
		return (1);
	close_pipes(l, 0);
	count2 = 0;
	while (count2 < count)
		waiter_input(l, count2++);
	if (*g_exit_code == 130 || *g_exit_code == 131 || *g_exit_code == 2)
		l->last_exit = *g_exit_code;
	return (0);
}

void	free_exec_input(t_lexer *l)
{
	ultime_close_archive(l);
	free(l->pip->pid);
	free(l->pip->ppd);
	free(l->pip);
	l->pip = NULL;
}

int	exec_input(t_lexer *l)
{
	t_node	*n;

	if (!l || !l->node || !l->tok || l->flagr[0] || !l->rl[0])
	{
		if (l)
			ultime_close_archive(l);
		return (0);
	}
	if (init_pip(l))
	{
		print_custom("init_pipe error", 1, 1, 1);
		return (1);
	}
	n = l->node;
	if (exec_input_split(l, n) == 1)
		return (1);
	signal_wait_input();
	free_exec_input(l);
	return (0);
}
