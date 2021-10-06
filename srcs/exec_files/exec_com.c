/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/10/04 20:17:47 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

char	*join_two_array(char *ptr, const char *ptr2)
{
	int	count;

	count = 0;
	while (ptr2[count])
	{
		ptr[count] = ptr2[count];
		count++;
	}
	ptr[count] = 0;
	return (ptr);
}

int	exec_com(t_lexer *l, t_node *n, int count)
{
	int	count2;
	int	tmp;

	if (n->type != NODE_NOCOM && n->type != NODE_PATHCOM)
	{
		printf("gros soucis, une non commamde a ete envoye dans exec_com\n");
		exit(1);
	}
	l->pip->pid[count + 1] = fork();
	if (!l->pip->pid[count + 1])
	{
		tmp = access(n->str[0], X_OK);
		if (tmp)
		{
			print_custom(n->str[0], 2, 1, 0);
			return(print_custom(" command not found\n", 2, 1, 1));
		}
		count2 = 0;
		/* while (n->right->str[count2])
		{
			if (n->right->type == NODE_)
		} */
		if (execve(n->str[0], n->str, l->envp))
		{
			printf("error comm\n");
			exit (1);
		}
	}
	return (0);
}
