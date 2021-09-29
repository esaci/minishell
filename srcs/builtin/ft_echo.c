/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:51:18 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 15:14:43 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

int	check_arg(char	*str)
{
	if (!str)
		return (-1);
	else if (!ft_strncmp(str, "|", 1) || !ft_strncmp(str, "&", 1) || !ft_strncmp(str, "\n", 1))
		return (-1);
	else
		return (1);
}

int	ft_echo_check(t_command *cmd)
{
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
	while (check_arg(cmd->args[i]) == 1)
	{
		write(cmd->fd_out, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
	}
}

void	ft_echo(t_command *cmd)
{
	cmd->flag = 0;
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
	if (cmd->flag != 1)
		write(cmd->fd_out, "\n", 1);
}