/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:39:47 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 17:52:47 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	search_command2(t_lexer *l, t_node *n, t_token *t, t_token *tmp2)
{
	int	count;

	count = nbr_com(l, tmp2);
	n->str = malloc(sizeof(char *) * (count + 3));
	if (!n->str)
		return (1);
	n->str[count] = NULL;
	n->str[0] = l->buffer[get_buffer_count(l, t)];
	if (search_node_str_com(n, t->n_token, l))
		return (1);
	return (0);
}

int	search_command(t_node *n, t_token *t, t_lexer *l)
{
	t_token	*tmp;
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
	return (search_command2(l, n, t, tmp2));
}

int	search_pipe(t_node *n, t_token *t, t_lexer *l)
{
	t_token	*tmp;

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

int	search_infile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;

	if (malloc_node_redir(n, t, CHAR_DCHEVG, CHAR_CHEVG))
		exit(small_free(NULL, NULL, NULL, 1));
	signal_wait_heredoc();
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if ((t->type == CHAR_CHEVG
				|| t->type == CHAR_DCHEVG) && !g_exit_code[0])
			search_chevg(n, t, l, &count);
		t = t->n_token;
	}
	n->str[count] = NULL;
	free_loop_fd_in(n);
	infile_exit_code();
	return (0);
}

int	search_outfile(t_node *n, t_token *t, t_lexer *l)
{
	int	count;

	if (malloc_node_redir(n, t, CHAR_CHEVD, CHAR_DCHEVD))
		return (1);
	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (t->type == CHAR_CHEVD || t->type == CHAR_DCHEVD)
			search_chevd(n, t, l, &count);
		t = t->n_token;
	}
	n->str[count] = NULL;
	free_loop_fd_out(n);
	return (0);
}
