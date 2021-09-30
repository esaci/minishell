/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:05:52 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 19:00:04 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

/*
void	ft_cd_noargs(t_command *cmd)
{
	
}
*/

void	ft_cd(t_command *cmd)
{
	printf("Commande : %s\n", *cmd->args);
	if (!ft_strncmp(*cmd->args, "\n", 1))
		printf(RED"KO\n"RESET);
	else
		printf(GREEN"OK\n"RESET);
}