/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:32:27 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 17:16:39 by julpelle         ###   ########.fr       */
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
		if (l->pip->ppd[count2] > -1)
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
