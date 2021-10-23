/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 18:38:08 by elias             #+#    #+#             */
/*   Updated: 2021/10/23 18:38:10 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	len_needed(t_lexer *l)
{
	int	count;
	int	count2;

	count = ft_strlen(lexer->rl);
	while (lexer->rl[count2])
}

int	init_line_buffer(t_lexer *l)
{
	int	count;

	if (l->line_buffer)
		free(l->line_buffer);
	count = len_needed(l);
}