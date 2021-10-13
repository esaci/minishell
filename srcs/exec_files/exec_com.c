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

int	join_close_token(t_lexer *l, char **str, int count)
{
	int		count2;
	t_token	*t;
	t_token	*t2;
	int		ad;

	count2 = 0;
	if (count && ft_strlen(str[count]) > 1)
	{
		t = get_token_buffer(l, str[count]);
		t2 = get_token_buffer(l, str[count - 1]);
		ad = 0;
		if (t2->line[0] != str[count - 1][0])
			ad = 2;
		if ((t2->line[ft_strlen(str[count - 1]) + ad] != ' ' && compatibility_arg(t2->type, 0)))
		{
			str[count - 1] = merge_twoarray(str[count - 1], str[count]);
			str[count] = NULL;
			count2 = count;
			while (str[count2] && str[count2 + 1])
			{
				str[count2] = str[count2 + 1];
				count2++;
			}
			str[count2] = NULL;
			if (t2->n_token && t2->n_token->n_token)
				t2->n_token = unlink_free_return(t2->n_token, 1);
		}
	}
	if (count < ft_strlen_double(str) && ft_strlen(str[count]) > 1)
	{
		t = get_token_buffer(l, str[count]);
		t2 = get_token_buffer(l, str[count + 1]);
		if ((t->line[ft_strlen(str[count]) + 2] != ' ' && t->line[ft_strlen(str[count]) + 2] != '\0' && compatibility_arg(t2->type, 1)))
		{
			str[count] = merge_twoarray(str[count], str[count + 1]);
			count2 = count;
			while (str[count2] && str[count2 + 1] && str[count2 + 2])
			{
				str[count2 + 1] = str[count2 + 2];
				count2++;
			}
			str[count2 + 1] = NULL;
			if (t->n_token && t->n_token->n_token)
				t->n_token = unlink_free_return(t->n_token, 1);
		}
	}
	return (0);
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
	int		tmp;
	int		fd[2];
	int		len;
	char	**ptr;

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
			exit(1);
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
		free(ptr[0]);
		free(ptr[1]);
		close_pipes(l, 1);
		check_for_arg(n->str, l, n);
		ptr[0] = parse_is_command(n->str[0], l, 0);
		free(n->str[0]);
		n->str[0] = ptr[0];
		free(ptr);
		tmp = access(n->str[0], X_OK);
		if (tmp || ft_strlen(n->str[0]) == 0)
		{
			if (n->str[0])
			{
				correct_name(l, n->str[0]);
				print_custom(n->str[0], 2, 1, 0);
				double_free(n->str);
				exit(print_custom(" command not found", 2, 1, 1));
			}
			double_free(n->str);
			exit(0);
		}
		if (execve(n->str[0], n->str, l->envp) == -1)
		{
			double_free(n->str);
			small_free(l, NULL, NULL, 1);
			exit(print_custom("error comm", 2, 1, 1));
		}
	}
	return (0);
}
