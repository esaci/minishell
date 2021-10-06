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

	if (!l || !l->node || !l->tok)
		return (0);
	if (init_pip(l))
	{
		print_custom("init_pipe error", 1, 1, 1);
		return (1);
	}
	n = l->node;
	count = 0;
	count2 = 0;
	while (n && n->type == NODE_PIPE)
	{
		count2 = id_pipe(l, n);
		n = exec_pipe(l, n);
		count += 2;
	}
	if (exec_com(l, n,  count++, count2))
		return (1);
	count2 = 0;
	while (count2 < count)
		waiter_input(l, count2++);
	free(l->pip);
	l->pip = NULL;
	return (0);
}
