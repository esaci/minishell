/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 04:01:36 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

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

void	exec_com_main_body(t_lexer *l, t_node *n, int count)
{
	int		fd[2];

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
}

int	exec_com(t_lexer *l, t_node *n, int count)
{
	t_token	*t;
	char	**ptr;
	int		tmp;

	exec_com_pipes(l, n, count);
	if (!l->pip->pid[count])
	{
		exec_com_main_body(l, n, count);
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
