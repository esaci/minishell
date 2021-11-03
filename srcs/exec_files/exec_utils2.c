/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 04:01:07 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/04 00:46:30 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	last_pipe(t_lexer *l)
{
	int		count;
	t_node	*n;

	n = l->node;
	count = 0;
	while (n && n->type == NODE_PIPE)
	{
		n = n->right;
		count++;
	}
	return (count);
}

void	utils2_com_nopipe(t_lexer *l, t_node *n, int count)
{
	int	tmp;

	tmp = -1;
	if (last_pipe(l) == 0 || count == last_pipe(l))
	{
		if (n && n->str && (n->str + 1))
			tmp = new_menu(n->str[0], n->str + 1, l);
		l->pip->pid[count] = fork();
		if (l->pip->pid[count])
		{
			if (n && n->left && n->left->left && n->left->left->archive_fd)
				close_archive(n->left->archive_fd);
		}
		if (tmp != -1 && !l->pip->pid[count])
		{
			close_pipes(l, 1);
			tmp = l->last_exit;
			small_free(l, NULL, NULL, 1);
			exit(tmp);
		}
		if (l->pip->pid[count])
			signal_wait_command();
	}
	else
		l->pip->pid[count] = 0;
}

void	error_pipe(t_lexer *l, int count)
{
	if (count == last_pipe(l))
	{
		close_pipes(l, 1);
		small_free(l, NULL, NULL, 1);
		exit(print_custom("Empty pipe", 2, 1, 1));
	}
	close_pipes(l, 1);
	small_free(l, NULL, NULL, 1);
	exit(1);
}

void	execve_check_error(t_lexer *l, t_node *n, char **ptr, int tmp)
{
	DIR		*dir_ptr;

	if (execve(n->str[0], n->str, ptr) == -1)
	{
		dir_ptr = opendir(n->str[0]);
		if (dir_ptr)
		{
			closedir(dir_ptr);
			print_custom(n->str[0], 2, 1, 0);
			tmp = 1;
		}
		else
			tmp = 0;
		double_free(ptr);
		small_free(l, NULL, NULL, 1);
		if (!tmp)
			exit(print_custom("error comm", 2, 1, 1));
		exit(print_custom(": Is a Directory", 2, 126, 1));
	}
}
