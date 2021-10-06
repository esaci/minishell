/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:51:18 by Jules             #+#    #+#             */
/*   Updated: 2021/10/04 19:20:11 by julespellet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

// PARSING 2

int	check_flag(t_command *cmd)
{
	int	i;

	i = 0;
	(void)cmd;
	return (i);
}

void	ft_echo(t_command *cmd)
{
	int	flag;

	flag = 0;
	check_flag(cmd);
}

/*
// PARSING 1

int	ft_echo_check(t_command *cmd)
{
	printf("ECHO CHECK 0 OK\n");
	if (!ft_strncmp(*cmd->args, "\n", 2))
		return (ERROR);
	if (!ft_strncmp(*cmd->args, "-", 2))
	{
		cmd->flag = 1;
		return (SUCCESS);
	}
	return (ERROR);
}

void	ft_print_echo(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		printf("TEST\n");
		write(cmd->fd_out, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
	}
}

void	ft_echo(t_command *cmd)
{
	cmd->flag = 0;
	printf("TEST 0 ECHO : OK\n");
	if (ft_echo_check(cmd) == SUCCESS)
	{
		cmd->args = (cmd->args + 1);
		if (!ft_strncmp(*cmd->args, "n", 1))
			cmd->flag = 1;
		else
			cmd->flag = 0;
	}
	if (cmd->flag == 1 && (cmd->args_cpy + 2))
		cmd->args = cmd->args_cpy + 2;
	else
		cmd->args = cmd->args_cpy;
	ft_print_echo(cmd);
	if (cmd->flag != 1 || !cmd->args)
		write(cmd->fd_out, "\n", 1);
	// /exit(1);
}
*/