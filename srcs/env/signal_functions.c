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

	print_custom("", 1, 1, 1);
	*g_exit_code = 130;
	fd = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	*g_exit_code = fd;
	return ;
	if (num)
		fd = dup(STDIN_FILENO);
	close(STDIN_FILENO);
}

void	handler_parent_muted(int num)
{
	if (num == SIGINT)
	{
		print_custom("", 1, 1, 1);
		*g_exit_code = 130;
	}
}

void	signal_wait_input(void)
{
	signal(SIGINT, handler_parent);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	signal_wait_command(void)
{
	signal(SIGINT, handler_parent_muted);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	signal_wait_heredoc(void)
{
	signal(SIGINT, handler_parent_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}