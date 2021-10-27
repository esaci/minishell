/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/10/27 13:00:19 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	join_close_token(t_lexer *l, char **str, int count)
{
	int		count2;
	t_token	*t;
	t_token	*t2;
	int		ad;
	int		counter[2];

	count2 = 0;
	if (count)
	{
		t = get_token_buffer(l, str[count - 1]);
		t2 = get_token_buffer(l, str[count]);
		ad = 0;
		if (correct_name(l, t))
			ad = 2;
		if ((t->line[ft_strlen(str[count - 1]) + ad] == t2->line[0] && compatibility_arg(t2->type, 0)))
		{
			counter[0] = get_buffer_count(l, t);
			counter[1] = get_buffer_count(l, t2);
			l->buffer[counter[0]] = merge_twoarray(l->buffer[counter[0]], l->buffer[counter[1]], 0);
			str[count - 1] = l->buffer[counter[0]];
			count2 = count;
			while (str[count2])
			{
				str[count2] = str[count2 + 1];
				count2++;
			}
			str[count2] = NULL;
			if (t->n_token)
				t->n_token = unlink_free_return(t->n_token, 1);
			return (--count);
		}
	}
	if (count < (ft_strlen_double(str) - 1))
	{
		t = get_token_buffer(l, str[count]);
		t2 = get_token_buffer(l, str[count + 1]);
		ad = 2;
		if (correct_name(l, t))
			ad = 2;
		if ((t->line[ft_strlen(str[count]) + ad] == t2->line[0] && compatibility_arg(t2->type, 0)))
		{
			counter[0] = get_buffer_count(l, t);
			counter[1] = get_buffer_count(l, t2);
			l->buffer[counter[0]] = merge_twoarray(l->buffer[counter[0]], l->buffer[counter[1]], 1);
			str[count] = l->buffer[counter[0]];
			count2 = count + 1;
			while (str[count2])
			{
				l->buffer[counter[1]] = l->buffer[counter[1] + 1];
				str[count2] = str[count2 + 1];
				count2++;
				counter[1]++;
			}
			l->buffer[counter[1]] = NULL;
			str[count2] = NULL;
			if (t->n_token)
				t->n_token = unlink_free_return(t->n_token, 1);
			return (count);
			
		}
	}
	return (++count);
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
	t_token	*t;
	char	**ptr;

	tmp = 0;
	if (last_pipe(l) == 0 || count == last_pipe(l))
	{
		if (n && n->str && (n->str + 1))
			tmp = new_menu(n->str[0], n->str + 1, l);
		signal_reset();
		l->pip->pid[count] = fork();
		if (tmp != -1 && !l->pip->pid[count])
		{
			close_pipes(l, 1);
			tmp = l->last_exit;
			small_free(l, NULL, NULL, 1);
			exit(tmp);
		}
	}
	else
		l->pip->pid[count] = 0;
	if (!l->pip->pid[count])
	{
		signal_default();
		if (!n || (n->type != NODE_NOCOM && n->type != NODE_PATHCOM))
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
		if (count != 0 && count == last_pipe(l))
		{
			close(l->pip->ppd[((count - 1) * 2) + 1]);
			dup2(l->pip->ppd[(count - 1) * 2], STDIN_FILENO);
		}
		ptr = malloc(sizeof(char*) * 3);
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
		close_pipes(l, 1);
		if (menu(n->str[0], n->str + 1, l) == -1)
		{
			small_free(l, NULL, NULL, 1);
			exit(print_custom("error comm", 2, 1, 1));
		}
		t = get_token_buffer(l, n->str[0]);
		l->buffer[get_buffer_count(l, t)] = parse_is_command(l->buffer[get_buffer_count(l, t)], l, 0, 1);
		n->str[0] = l->buffer[get_buffer_count(l, t)];
		tmp = access(n->str[0], X_OK);
		if (tmp || !ft_strlen(n->str[0]))
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
		ptr = generate_custom_envp(l->envp);
		if (execve(n->str[0], n->str, ptr) == -1)
		{
			free(ptr);
			small_free(l, NULL, NULL, 1);
			exit(print_custom("error comm", 2, 1, 1));
		}
	}
	return (0);
}
