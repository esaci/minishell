/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:10:27 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/30 12:10:35 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	handler_parent(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		print_custom("", 1, 1, 1);
		rl_replace_line("", 0);
		rl_redisplay();
		*g_exit_code = 130;
	}
}

void	handler_parent_heredoc(int num)
{
	int		fd;

	if (num == SIGINT)
	{
		print_custom("", 1, 1, 1);
		*g_exit_code = 130;
		fd = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		*g_exit_code = fd;
	}
}

void	handler_parent_muted(int num)
{
	if (num == SIGINT)
	{
		print_custom("", 1, 1, 1);
		*g_exit_code = 130;
	}
	if (num == SIGQUIT)
	{
		print_custom("Quit (core dumped)", 1, 1, 1);
		*g_exit_code = 131;
	}
}

void	handler_child_sigquit(int num)
{
	if (num == SIGQUIT)
		kill(0, SIGQUIT);
}
