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

	l->pip->pid[count] = fork();
	if (!l->pip->pid[count])
	{
		in = (count - 1) * 2;
		out = in + 3;
		if (count > 0)
			dup2(l->pip->ppd[in], STDIN_FILENO);
		dup2(l->pip->ppd[out], STDOUT_FILENO);
		exit_code = exec_com(l, n->left, count);
		exit(exit_code);
	}
	n = n->right;
	return (n);
}
