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

void	signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
		print_custom("", 1, 1, 1);
        rl_replace_line("", 0);
        rl_redisplay();
        g_exit_code = 130;
    }
    if (sig == SIGQUIT)
    {
        print_custom("Quit : 3", 1, 1, 1);
        g_exit_code = 131;
    }
}

void	get_signal(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}

void    signal_reset(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}