/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 00:45:11 by elias             #+#    #+#             */
/*   Updated: 2021/10/28 00:45:13 by elias            ###   ########.fr       */
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

void	signal_wait_input(void)
{
	signal(SIGINT, handler_parent);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	signal_wait_command(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, handler_parent_muted);
	signal(SIGQUIT, handler_parent_muted);
	signal(SIGTERM, SIG_IGN);
}

void	signal_wait_heredoc(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handler_parent_heredoc);
}

void	signal_default(void)
{
	signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}