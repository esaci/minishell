/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_free_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:01:22 by elias             #+#    #+#             */
/*   Updated: 2021/10/29 18:01:26 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	small_free(t_lexer *l, void *ptr, void *ptr2, int mode)
{
	free_lexer_tokens(l, 0);
	free_lexer_nodes(l, 0);
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (mode && l)
	{
		double_free(l->pwd);
		double_free(l->pathptr);
		free_env(l->envp);
		if (l->rl)
			free(l->rl);
		if (l->line_buffer)
			free(l->line_buffer);
		free(l);
		return (0);
	}
	return (0);
}

int	small_finish_free(t_lexer *l, void *ptr, void *ptr2)
{
	if (l)
	{
		double_free(l->pwd);
		double_free(l->pathptr);
		free_env(l->envp);
		if (l->line_buffer)
			free(l->line_buffer);
		free(l);
	}
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	return (0);
}
