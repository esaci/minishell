/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:50:15 by esaci             #+#    #+#             */
/*   Updated: 2021/10/27 12:57:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	ultime_close_archive(t_lexer *l)
{
	t_node *n;

	n = l->node;
	while (n && n->type == NODE_PIPE)
	{
		close_archive(n->left->left->fd);
		n = n->right;
	}
	if (n)
		close_archive(n->left->fd);
}

int	exec_input(t_lexer *l)
{
	t_node	*n;
	int		count;
	int		count2;

	if (!l || !l->node || !l->tok || l->flagr[0] || !l->rl[0])
	{
		ultime_close_archive(l);
		return (0);
	}
	if (init_pip(l))
	{
		print_custom("init_pipe error", 1, 1, 1);
		return (1);
	}
	n = l->node;
	count = 0;
	while (n && n->type == NODE_PIPE)
		n = exec_pipe(l, n, count++);
	if (exec_com(l, n,  count++))
		return (1);
	close_pipes(l, 0);
	count2 = 0;
	while (count2 < count)
		waiter_input(l, count2++);
	signal_wait_input();
	free(l->pip->pid);
	free(l->pip->ppd);
	free(l->pip);
	l->pip = NULL;
	return (0);
}
