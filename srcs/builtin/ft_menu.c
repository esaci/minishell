/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:55:38 by Jules             #+#    #+#             */
/*   Updated: 2021/10/07 09:40:53 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

int	ft_max(char *str1, char *str2)
{
	return (ft_strlen(str1) >= ft_strlen(str2)
		? ft_strlen(str1) : ft_strlen(str2));
}

int	ft_iscommand(char *cmd)
{
	t_builtin		builtin[] = {{"echo"}, {"cd"}, {"pwd"},
	{"export"}, {"env"}, {"unset"}, {"exit"}};
	
	unsigned int	i;

	i = 0;
	while (i < sizeof(builtin) / sizeof(*builtin))
	{
		if (!ft_strncmp(cmd, builtin[i].str, ft_strlen(builtin[i].str)))
		{
			printf("Command is "GREEN"%s\n"RESET, builtin[i].str);
			return (i);
		}
		i++;
	}
	/*
	if (i == sizeof(builtin) / sizeof(*builtin))
		printf(RED"%s : Command not found\n"RESET, cmd);
	*/
	return (-1);
}

void	ft_menu(t_command *cmd)
{
	if (!ft_strncmp(cmd->name, "echo", 4))
		ft_echo(cmd);
	if (!ft_strncmp(cmd->name, "pwd", 3))
		ft_pwd(cmd);
	if (!ft_strncmp(cmd->name, "cd", 3))
		ft_cd(cmd);
	if (!ft_strncmp(cmd->name, "env", 3))
		ft_env(cmd);
	else
		;
}

void	ft_show_double(char **av)
{
	int i;

	i = 0;
	if (!av[i])
	{
		while (av[i])
		{
			printf("%s\n", av[i]);
			i++;
		}
	}
}

int	exec_command(char **buffer)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command) * 2);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->name = ft_strdup(buffer[0]);
	cmd->operation = ft_iscommand(cmd->name);
	if (cmd->operation < 0)
		return (0);
	if (cmd->operation >= 0)
	{
		cmd->args = buffer;
		cmd->args_cpy = buffer;
		ft_menu(cmd);
	}
	free(cmd->name);
	return (0);
}
