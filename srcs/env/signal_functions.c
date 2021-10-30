/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 00:45:11 by elias             #+#    #+#             */
/*   Updated: 2021/10/30 12:11:02 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

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
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handler_child_sigquit);
}
