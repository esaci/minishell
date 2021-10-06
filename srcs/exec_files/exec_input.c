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

	if (!l || !l->node || !l->tok)
		return (0);
	if (init_pip(l))
		return (1);
	n = l->node;
	count = 0;
	while (n && n->type == NODE_PIPE)
	{
		n = exec_pipe(l, n);
		count++;
	}
	if (!exec_com(l, n,  count))
		return (1);
	count = 0;
	while (l->pip->pid[count] != -2)
		waiter_input(l, count);
	free(l->pip);
	l->pip = NULL;
	return (0);
}
