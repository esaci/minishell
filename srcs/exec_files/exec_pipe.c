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

	l->pip->pid[count] = fork();
	if (!l->pip->pid[count])
	{
		if (count > 0)
			dup2(l->pip->ppd[count - 1], STDIN_FILENO);
		if (count < last_pipe(l))
			dup2(l->pip->ppd[count], STDOUT_FILENO);
		exit_code = exec_com(l, n->left, count);
	}
	n = n->right;
	return (n);
}
