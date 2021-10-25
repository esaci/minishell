/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:13:38 by esaci             #+#    #+#             */
/*   Updated: 2021/09/26 00:13:41 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

static void minish (int sig, siginfo_t *siginfo, void *context)
{
	print_custom("^C", 1, 1, 1);
	/* kill(0, SIGINT); */
	(void)sig;
	(void)siginfo;
	(void)context;
}

void	*sig_handler()
{
	void	(*sigint_c)(int);
	struct sigaction act;

	act.sa_sigaction = &minish;
	sigint_c = signal(SIGINT, SIG_IGN);
	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror ("sigaction");
	}
	signal(SIGTSTP, SIG_IGN);
	return (sigint_c);
}
