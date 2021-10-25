/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:32:27 by esaci             #+#    #+#             */
/*   Updated: 2021/10/05 22:32:30 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	full_close(t_lexer *l)
{
	t_node	*n;
	int		count;
	int		count2;

	n = l->node;
	count = 0;
	while (n)
	{
		if (n->type == NODE_PIPE)
			count++;
		n = n->right;
	}
	count2 = 0;
	while (count2 < count)
	{
		close(l->pip->ppd[count2]);
		count2++;
	}
	return (0);
}

int	full_free(t_lexer *l)
{
	free_lexer_tokens(l, 1);
	return (free_pip(l, 0));
}
