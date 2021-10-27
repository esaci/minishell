/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 23:13:29 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/27 12:56:54 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

void        handler_son(int num)
{
/* 	int	fd; */

	if (num == SIGINT)
	{
		if (!g_exit_code)
		{
			g_exit_code = 130;
/* 			fd = open("./srcs/here_doc_file", O_RDWR);
			print_custom("", fd, 1, 0); */
/* 			rl_replace_line("", 0);
			rl_redisplay(); */
		}
		g_exit_code = 130;
	}
	else if (num == SIGQUIT)
	{
		print_custom("", 1, 1, 1);
		print_custom("Quit (core dumped)", 1, 1, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 131;
	}
}

void	signal_wait_input(void)
{
	signal(SIGINT, SIG_IGN);
/* 	signal(SIGINT, signal_handler); */
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	get_signal_child(void)
{
	signal(SIGINT, SIG_IGN);
	/* signal(SIGINT, signal_handler); */
	signal(SIGQUIT, handler_son);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}