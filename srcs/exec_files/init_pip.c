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
	int		count2;

	n = l->node;
	count = 0;
	while (n)
	{
		if (n->type == NODE_PIPE)
			count++;
		n = n->right;
	}
	l->pip->ppd = malloc(sizeof(int) * ((count + 6) * 2));
	if (!l->pip->ppd)
	{
		free(l->pip->pid);
		return (1);
	}
	count2 = 0;
	while(count2 < (count + 3))
	{
		if (pipe(l->pip->ppd + (count2 * 2)) == -1)
			return(free_pip(l, 1));
		count2++;
	}
	return (0);
}

int	init_pip(t_lexer *l)
{
	int	count;
	int	count2;

	l->pip = malloc(sizeof(t_pip) * 2);
	if (!l->pip)
		return (1);
	count = count_right_nodes(l);
	l->pip->pid = malloc(sizeof(int) * ((count * 2) + 10));
	if (!l->pip->pid)
		return (1);
	count2 = 0;
	while (count2 < (count * 2 + 9))
		l->pip->pid[count2++] = -2;
	return (init_pip2(l));
}

void	close_pipes(t_lexer *l)
{
	int		count;
	int		count2;
	t_node	*n;

	n = l->node;
	count = 0;
	while (n)
	{
		if (n->type == NODE_PIPE)
			count++;
		n = n->right;
	}
	count2 = 0;
	while(count2 <	((count + 3)* 2))
		close(l->pip->ppd[count2++]);
/* 	free(l->pip->pid);
	free(l->pip->ppd);
	free(l->pip);
	l->pip = NULL; */
}