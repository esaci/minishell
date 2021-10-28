/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:39:47 by esaci             #+#    #+#             */
/*   Updated: 2021/10/02 20:39:48 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	search_node_str_com(t_node *n, t_token *t, t_lexer *l)
{
	int		count;
	t_token *tmp;

	if (n->type != NODE_NOCOM && n->type != NODE_PATHCOM)
		return (0);
	count = 1;
	tmp = t;
	while (t && t->type != CHAR_PIPE)
	{
		if ((t->type == CHAR_INUT && !is_any_chevron(tmp)) || (is_arg(t) == 1))
		{
			n->str[count] = l->buffer[get_buffer_count(l, t)];
			count++;
		}
		tmp = t;
		t = t->n_token;
	}
	n->str[count] = NULL;
	return (0);
	return(l->buffer[0][0]);
}

int	search_command(t_node *n, t_token *t, t_lexer *l)
{
	t_token *tmp;
	t_token	*tmp2;
	int		count;

	tmp = t;
	tmp2 = t;
	while (t && (is_any_chevron(tmp) || !is_arg(t)))
	{
		tmp = t;
		t = t->n_token;
	}
	if (!t)
	{
		n->type = NODE_NOCOM;
		no_com_fill(n, l, tmp2);
		return (0);
	}
	count = is_any_command(l, t, tmp);
	if (count)
		n->type = NODE_PATHCOM;
	else
		n->type = NODE_NOCOM;
	count = nbr_com(l, tmp2);
	n->str = malloc(sizeof(char*) * (count + 3));
	if (!n->str)
		return (1);
	n->str[count] = NULL;
	n->str[0] = l->buffer[get_buffer_count(l, t)];
	if (search_node_str_com(n, t->n_token, l))
		return (1);
	return (0);
}

int	search_pipe(t_node *n, t_token *t, t_lexer *l)
{
	t_token *tmp;

	tmp = t;
	while (t && t->type != CHAR_PIPE)
		t = t->n_token;
	if (t)
	{
		n->type = NODE_PIPE;
		n->str = NULL;

	}
	else
	{
		if (search_command(n, tmp, l))
			return (1);
	}
	return (0);
}

int	*join_int(int *fd, char *str, t_lexer *l)
{
	int	*ptr;
	int	count;

	if (!fd)
	{
		ptr = malloc(sizeof(int) * 2);
		ptr[0] = -1;
		ptr[1] = -1;
		exec_in_heredoc(str, ptr, l);
		return (ptr);
	}
	count = 0;
	while (fd && fd[count] != -1)
		count++;
	ptr = malloc(sizeof(int) * (count + 2));
	count = 0;
	while (fd && fd[count] != -1)
	{
		ptr[count] = fd[count];
		count++;
	}
	exec_in_heredoc(str, ptr + count, l);
	ptr[count + 1] = -1;
	free(fd);
	return (ptr);
}

int	search_infile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;
	int	count2;
	t_token	*tmp;

	n->left = NULL;
	n->right = NULL;
	n->fd = NULL;
	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVG || tmp->type == CHAR_DCHEVG)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * ((count*2) + 2));
	if (!n->str)
		return (1);
	signal_wait_heredoc();
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if ((t->type == CHAR_CHEVG || t->type == CHAR_DCHEVG) && !g_exit_code[0])
		{
			count2 = get_buffer_count(l, t);
			n->str[count] = l->buffer[count2];
			count++;
			n->type = NODE_FILEIN;
			if (t->type == CHAR_DCHEVG)
			{
				if (t->n_token && t->n_token->type == CHAR_INUT)
					n->fd = join_int(n->fd, l->buffer[get_buffer_count(l, t->n_token)], l);
				else
				{
					free(n->fd);
					n->fd = NULL;
				}
				n->type = NODE_DFILEIN;
			}
			if (add_path(&n->str[count], t, l, n->str[count - 1]))
				return (2);
			count++;
		}
		t = t->n_token;
	}
	n->str[count] = NULL;
	if (!n->str[0])
	{
		if (n->fd)
		{
			count = 0;
			while (n->fd[count] != -1)
				close(n->fd[count]);
			free(n->fd);
		}
		n->type = NODE_FILEIN;
		n->str[0] = "/dev/stdin";
		n->str[1] = 0;
	}
	if (*g_exit_code)
	{
		signal_wait_input();
		dup2(*g_exit_code, STDIN_FILENO);
		close(*g_exit_code);
		*g_exit_code = 130;
	}

	return (0);
}

int	search_outfile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;
	t_token	*tmp;

	n->left = NULL;
	n->right = NULL;
	n->fd = NULL;
	tmp = t;
	count = 0;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		if (tmp->type == CHAR_CHEVD || tmp->type == CHAR_DCHEVD)
			count++;
		tmp = tmp->n_token;
	}
	n->str = malloc(sizeof(char*) * ((count*2) + 2));
	if (!n->str)
		return (1);
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_CHEVD || t->type == CHAR_DCHEVD)
		{
			n->str[count] = l->buffer[get_buffer_count(l, t)];
			count++;
			n->type = NODE_FILEOUT;
			if (t->type == CHAR_DCHEVD)
				n->type = NODE_DFILEOUT;
			if (add_path(&n->str[count], t, l, n->str[count - 1]))
				return (2);
			count++;
		}
		t = t->n_token;
	}
	n->str[count] = NULL;
	if (!n->str[0])
	{
		n->type = NODE_FILEOUT;
		n->str[0] = "/dev/stdout";
		n->str[1] = 0;

	}
	return (0);
}

/* if (!is_any_chevron(tmp2) && !is_arg(t))
			{
				n->str[count2] = l->buffer[count];
				count2++;
			} */
