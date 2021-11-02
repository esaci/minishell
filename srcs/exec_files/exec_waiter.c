/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_waiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:21:19 by esaci             #+#    #+#             */
/*   Updated: 2021/10/06 18:21:21 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	waiter_input(t_lexer *l, int count)
{
	l->pip->tmp[0] = 0;
	waitpid(l->pip->pid[count], &(l->pip->tmp[1]), 0);
	if (WIFEXITED(l->pip->tmp[1]))
	{
		l->pip->tmp[0] = WEXITSTATUS(l->pip->tmp[1]);
		l->last_exit = l->pip->tmp[0];
		*g_exit_code = l->last_exit;
	}
	else
		l->last_exit = 0;
	return (0);
}
