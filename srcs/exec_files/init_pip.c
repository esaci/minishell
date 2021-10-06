/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:28:39 by esaci             #+#    #+#             */
/*   Updated: 2021/10/05 15:28:40 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	free_pip(t_lexer *l, int exit)
{
	free(l->pip->pid);
	free(l->pip->pfd);
	free(l->pip->ppd);
	return (exit);
}

int	init_pip2(t_lexer *l)
{
	t_node	*n;
	int		count;
	int		count2;

	n = l->node;
	count = 0;
	while (n)
	{
		if (n->type == NODE_PIPE)
			count++;
		n = n->right;
	}
	l->pip->ppd = malloc(sizeof(int) * ((count + 3) * 2));
	if (!l->pip->ppd)
	{
		free(l->pip->pid);
		free(l->pip->pfd);
		return (1);
	}
	count2 = 0;
	while(count2 < count)
	{
		if (pipe(l->pip->ppd + (count2 * 2)) == -1)
			return(free_pip(l, 1));
		count++;
	}
	return (0);
}

int	init_pip(t_lexer *l)
{
	t_node *n;
	int	count;
	int	count2;

	l->pip = malloc(sizeof(t_pip) * 2);
	if (!l->pip)
		return (1);
	n = l->node;
	count = 0;
	while (n)
	{
		count++;
		n = n->right;
	}
	l->pip->pid = malloc(sizeof(int) * ((count*2) + 2));
	if (!l->pip->pid)
		return (1);
	l->pip->pfd = malloc(sizeof(int) * (count * 2));
	if(!l->pip->pfd)
	{
		free(l->pip->pid);
		return (1);
	}
	count2 = 0;
	while (count2 < count)
		l->pip->pid[count2++] = -2;
	return (init_pip2(l));
}
