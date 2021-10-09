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

void	replace_for_arg(char *str)
{
	int	count;

	count = 0;
	while (str[count + 1])
	{
		str[count] = str[count + 1];
		count++;
	}
	str[count - 1] = '\0';
}

void	check_for_arg(char **str)
{
	int	count;

	count = 0;
	while (str && str[count])
	{
		if (str[count][0] == '\'' || str[count][0] == '\"')
		{
			if (ft_strlen(str[count]) > 2)
			{
				if (str[count][0] == str[count][ft_strlen(str[count]) - 1])
					replace_for_arg(str[count]);
			}
		}
		count++;
	}

}

int		last_pipe(t_lexer *l)
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

int	exec_com(t_lexer *l, t_node *n, int count)
{
	int	tmp;
	int	fd[2];
	int	len;
	char **ptr;

	if (last_pipe(l) == 0 || count == last_pipe(l))
		l->pip->pid[count] = fork();
	else
		l->pip->pid[count] = 0;
	if (!l->pip->pid[count])
	{
		if (!n || (n->type != NODE_NOCOM && n->type != NODE_PATHCOM))
		{
			if (count == last_pipe(l))
				exit(print_custom("Empty pipe", 2, 1, 1));
		}
		if (count != 0 && count == last_pipe(l))
		{
			close(l->pip->ppd[((count - 1) * 2) + 1]);
			dup2(l->pip->ppd[(count - 1) * 2], STDIN_FILENO);
		}
		ptr = malloc(sizeof(char*) * 3);
		if (!ptr)
			exit(1);
		ptr[2] = NULL;
		len = count_file_redirection(n->right, n->left);
		l->pip->pfd = malloc(sizeof(int) * (len + 1));
		if (!l->pip->pfd)
			exit(print_custom("Malloc dans exec-com error", 2, 1, 1));
		ptr[0] = open_infiles(n->left, &(fd[0]));
		ptr[1] = open_outfiles(n->right, &(fd[1]));
		if (fd[0] < 0 || fd[1] < 0)
			exit(check_order_redirection(l, ptr));
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
		close_pipes(l);
		tmp = access(n->str[0], X_OK);
		if (tmp)
		{
			if (n->str[0])
				print_custom(n->str[0], 2, 1, 0);
			exit(print_custom(" command not found", 2, 1, 1));
		}
		check_for_arg(n->str);
		if (execve(n->str[0], n->str, l->envp) == -1)
			exit(print_custom("error comm", 2, 1, 1));
	}
	return (0);
}
