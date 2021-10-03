/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:23:40 by esaci             #+#    #+#             */
/*   Updated: 2021/10/03 22:23:41 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	nbr_com(t_lexer *l, t_token *t)
{
	int	count;

	count = 0;
	while (t && t->type != CHAR_PIPE)
	{
		if (is_any_command(l, t))
			count++;
		t = t->n_token;
	}
	return (count);
}
