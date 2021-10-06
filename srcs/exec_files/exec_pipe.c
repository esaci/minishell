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

t_node	*exec_pipe(t_lexer *l, t_node *n)
{
	int	count;
	int	exit_code;

	count = id_pipe(l, n);
	l->pip->pid[(count * 2 ) + 1] = fork();
	if (count > 0)
		dup2(l->pip->ppd[count - 1], STDIN_FILENO);
	dup2(l->pip->ppd[count], STDOUT_FILENO);
	exit_code = exec_com(l, n->left, id_pipe(l, n), 0);
	n = n->right;
	return (n);
}
