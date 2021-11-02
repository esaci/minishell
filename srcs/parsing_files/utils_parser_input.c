/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 00:22:42 by elias             #+#    #+#             */
/*   Updated: 2021/11/02 17:35:50 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

t_token	*parser_chevron(t_token *t, enum TOKENTYPE type)
{
	t_token	*tmp;

	if (t->n_token->type == type)
	{
		t->type = t->type - 1;
		while (t->n_token->n_token && t->n_token->n_token->type == CHAR_SPACE)
			t->n_token->n_token = unlink_free_return(t->n_token->n_token, 1);
		return (unlink_free_return(t->n_token, 1));
	}
	else
	{
		tmp = t->n_token;
		while (tmp && tmp->type == CHAR_SPACE)
			tmp = unlink_free_return(tmp, 1);
	}
	return (tmp);
}

t_token	*parser_in_between(t_token *t, enum TOKENTYPE type)
{
	t_token	*tmp;

	tmp = check_apo(t, 1);
	if (tmp)
		return (tmp);
	tmp = t->n_token;
	while (tmp && tmp->line[0] != type)
		tmp = unlink_free_return(tmp, 1);
	if (!tmp)
		return (tmp);
	tmp = unlink_free_return(tmp, 1);
	while (tmp && tmp->type == CHAR_SPACE)
		tmp = unlink_free_return(tmp, 1);
	return (tmp);
}

t_token	*parser_until_not(t_token *t, enum TOKENTYPE type, enum TOKENTYPE type2)
{
	t_token	*tmp;

	tmp = t->n_token;
	while (tmp && tmp->type == type)
		tmp = unlink_free_return(tmp, 1);
	while (tmp && tmp->type == type2)
		tmp = unlink_free_return(tmp, 1);
	return (tmp);
}

t_token	*parser_until_space(t_token *tok)
{
	t_token	*tmp;

	tmp = tok->n_token;
	if (tok->type == CHAR_PIPE)
	{
		while (tmp && tmp->type == CHAR_SPACE)
			tmp = unlink_free_return(tmp, 1);
		if (!tmp || tmp->type == CHAR_PIPE)
		{
			if (!g_exit_code[0])
				print_custom(
					"Minishell: syntax error near unexpected token `|'",
					2, 1, 1);
			*g_exit_code = 2;
		}
		return (tmp);
	}
	while (tmp && tmp->type != CHAR_SPACE)
		tmp = unlink_free_return(tmp, 1);
	if (!tmp)
		return (tmp);
	tmp = unlink_free_return(tmp, 1);
	return (tmp);
}
