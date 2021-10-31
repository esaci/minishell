/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:24:22 by elias             #+#    #+#             */
/*   Updated: 2021/10/31 02:24:25 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	flag_arg(int count, int count2, t_lexer *l)
{
	if (l->rl[count2] == '<'
		&& l->rl[count2 + 1] && l->rl[count2 + 1] == '<')
		count = 2;
	if ((count == 1) && l->rl[count2] == ' ')
		count--;
	if ((count == 2) && l->rl[count2] != '<')
		count--;
	return (count);
}

int	malloc_free_buff(t_lexer *l)
{
	if (l->line_buffer)
		free(l->line_buffer);
	l->line_buffer = malloc(sizeof(char) * (len_needed(l) + 10));
	if (!l->line_buffer)
		return (1);
	return (0);
}

void	ignore_all_buff(t_lexer *l, int	*c2, int *c4)
{
	l->line_buffer[(*c4)++] = l->rl[(*c2)++];
	while (l->rl[(*c2)] && l->rl[(*c2)] != '\'')
		l->line_buffer[(*c4)++] = l->rl[(*c2)++];
	l->line_buffer[(*c4)++] = l->rl[(*c2)++];
}
