/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 03:16:10 by julpelle         ###   ########.fr       */
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

void	exec_com_pipes(t_lexer *l, t_node *n, int count)
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

void	free_last_pipe(t_lexer *l, int count)
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

void	exec_com_end(t_lexer *l, t_node *n, char **ptr, int tmp)
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

void	free_lexer_tmp(t_lexer *l, t_node *n, int tmp)
{
	if (tmp || !n->str[0])
	{
		if (n->str[0])
		{
			perror(n->str[0]);
			if (!access(n->str[0], F_OK))
			{
				small_free(l, NULL, NULL, 1);
				exit(126);
			}
			small_free(l, NULL, NULL, 1);
			exit(127);
		}
		small_free(l, NULL, NULL, 1);
		exit(0);
	}
}

void	init_ptr(t_lexer *l, t_node *n, int fd[2])
{
	char	**ptr;

	ptr = malloc(sizeof(char *) * 3);
	if (!ptr)
		exit(small_free(l, NULL, NULL, 1));
	ptr[2] = NULL;
	ptr[0] = open_infiles(n->left, &(fd[0]));
	ptr[1] = open_outfiles(n->right, &(fd[1]));
	if (fd[0] < 0 || fd[1] < 0)
		exit(check_order_redirection(l, ptr));
	free(ptr[0]);
	free(ptr[1]);
	free(ptr);
	if (fd[1] != 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[0] != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	exec_com(t_lexer *l, t_node *n, int count)
{
	int		fd[2];
	t_token	*t;
	char	**ptr;
	int		tmp;

	exec_com_pipes(l, n, count);
	if (!l->pip->pid[count])
	{
		if (!n || (n->type != NODE_NOCOM && n->type != NODE_PATHCOM))
			free_last_pipe(l, count);
		if (count != 0 && count == last_pipe(l))
		{
			close(l->pip->ppd[((count - 1) * 2) + 1]);
			dup2(l->pip->ppd[(count - 1) * 2], STDIN_FILENO);
		}
		init_ptr(l, n, fd);
		ultime_close_archive(l);
		close_pipes(l, 1);
		if (menu(n->str[0], n->str + 1, l) == -1)
		{
			small_free(l, NULL, NULL, 1);
			exit(print_custom("error comm", 2, 1, 1));
		}
		signal_default();
		tmp = 1;
		if (n->str[0])
		{
			t = get_token_buffer(l, n->str[0]);
			l->buffer[get_buffer_count(l, t)] = \
			parse_is_command(l->buffer[get_buffer_count(l, t)], l, 0, 1);
			n->str[0] = l->buffer[get_buffer_count(l, t)];
			tmp = access(n->str[0], X_OK);
		}
		free_lexer_tmp(l, n, tmp);
		ptr = generate_custom_envp(l->envp);
		exec_com_end(l, n, ptr, tmp);
	}
	return (0);
}
