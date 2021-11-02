/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:06:08 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 02:00:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	free_pip_2(t_lexer *l)
{
	if (!l->pip->ppd)
	{
		free(l->pip->pid);
		return (1);
	}
	return (0);
}

char	*merge_suite(int mode, char *ptr, char *s, char *d)
{
	if (mode == 3)
		return (ptr);
	if (mode == 2)
	{
		free(d);
		return (ptr);
	}
	if (s)
		free(s);
	if (!mode)
		return (ptr);
	if (d)
		free(d);
	return (ptr);
}