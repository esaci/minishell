/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fast_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:26:50 by esaci             #+#    #+#             */
/*   Updated: 2021/10/05 17:26:52 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	id_pipe(t_lexer *l, t_node *n)
{
	t_node	*tmp;
	int		count;

	tmp = l->node;
	count = 0;
	while (tmp && tmp != n)
	{
		count++;
		tmp = tmp->right;
	}
	return (count);
}
