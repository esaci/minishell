/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/10/04 20:17:47 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	exec_com(t_lexer *l, t_node *n)
{
	int	tmp;

	tmp = access(n->str[0], X_OK);
	if (tmp)
	{
		print_custom(n->str[0], 1, 1, 0);
		return(print_custom(" command not found\n"));
	}
	while (n)
		ft_strjoin(ptr, )
	return (0);
}
