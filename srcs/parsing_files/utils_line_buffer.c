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
