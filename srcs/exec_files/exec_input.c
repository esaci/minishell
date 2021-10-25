/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:50:15 by esaci             #+#    #+#             */
/*   Updated: 2021/10/04 19:50:41 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	exec_input(t_lexer *l)
{
	t_node	*n;
	int		count;
	int		count2;

	if (!l || !l->node || !l->tok || l->flagr || !l->rl[0])
		return (0);
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
	/* printf("|%d|\n", l->last_exit); */
	free(l->pip->pid);
	free(l->pip->ppd);
	free(l->pip);
	l->pip = NULL;
	return (0);
}
