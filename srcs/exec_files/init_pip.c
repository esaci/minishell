/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:28:39 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 17:29:42 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	count_right_nodes(t_lexer *l)
{
	t_node	*n;
	int		count;

	n = l->node;
	count = 0;
	while (n)
	{
		count++;
		n = n->right;
	}
	return (count);
}

int	free_pip(t_lexer *l, int exit)
{
	free(l->pip->pid);
	free(l->pip->ppd);
	return (exit);
}

int	init_pip2(t_lexer *l)
{
	t_node	*n;
	int		count;

	n = l->node;
	count = 0;
	while (n)
	{
		if (n->type == NODE_PIPE)
			count++;
		n = n->right;
	}
	l->pip->ppd = malloc(sizeof(int) * (3));
	if (!l->pip->ppd)
		exit(small_free(l, NULL, NULL, 1));
	if (free_pip_2(l) == 1)
		return (1);
	if (pipe(l->pip->ppd) == -1)
		return (free_pip(l, 1));
	return (0);
}

int	init_pip(t_lexer *l)
{
	int	count;
	int	count2;

	l->pip = malloc(sizeof(t_pip) * 2);
	if (!l->pip)
		exit(small_free(l, NULL, NULL, 1));
	count = count_right_nodes(l);
	l->pip->pid = malloc(sizeof(int) * ((count * 2) + 10));
	if (!l->pip->pid)
		exit(small_free(l, NULL, NULL, 1));
	count2 = 0;
	while (count2 < (count * 2 + 9))
		l->pip->pid[count2++] = -2;
	return (init_pip2(l));
}

void	close_pipes(t_lexer *l, int mode)
{
	if (l->pip->ppd[0] > -1)
		close(l->pip->ppd[0]);
	if (l->pip->ppd[1] > -1)
		close(l->pip->ppd[1]);
	if (!mode)
		return ;
	free(l->pip->pid);
	free(l->pip->ppd);
	free(l->pip);
	l->pip = NULL;
}
