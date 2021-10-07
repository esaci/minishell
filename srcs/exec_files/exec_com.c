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

int		last_pipe(t_lexer *l)
{
	int		count;
	t_node	*n;

	n = l->node;
	count = 0;
	while (n->type == CHAR_PIPE)
	{
		n = n->right;
		count++;
	}
	return (count);
}

int	exec_com(t_lexer *l, t_node *n, int count)
{
	int	tmp;
	int	fd[2];
	int	len;
	char **ptr;

	if (n->type != NODE_NOCOM && n->type != NODE_PATHCOM)
	{
		printf("gros soucis, une non commamde a ete envoye dans exec_com\n");
		exit(1);
	}
	if (count == last_pipe(l))
		l->pip->pid[count] = fork();
	else
		l->pip->pid[count] = 0;
	if (!l->pip->pid[count])
	{
		if (count != 0)
			dup2(l->pip->ppd[count - 1], STDIN_FILENO);
		ptr = malloc(sizeof(char*) * 3);
		if (!ptr)
			exit(1);
		ptr[2] = NULL;
		len = count_file_redirection(n->right, n->left);
		l->pip->pfd = malloc(sizeof(int) * (len + 1));
		if (!l->pip->pfd)
			exit(print_custom("malloc dans exec-com error", 2, 1, 1));
		ptr[0] = open_infiles(n->left, &(fd[0]));
		ptr[1] = open_outfiles(n->right, &(fd[1]));
		if (fd[0] < 0 || fd[1] < 0)
			exit(check_order_redirection(l, ptr));
		if (fd[1] != 1)
			dup2(fd[1], STDOUT_FILENO);
		if (fd[0])
			dup2(fd[0], STDIN_FILENO);
		tmp = access(n->str[0], X_OK);
		if (tmp)
		{
			if (n->str[0])
				print_custom(n->str[0], 2, 1, 0);
			exit(print_custom(" command not found", 2, 1, 1));
		}
		if (execve(n->str[0], n->str, l->envp) == -1)
			exit(print_custom("error comm", 2, 1, 1));
	}
	return (0);
}
