/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:55:38 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 15:20:24 by Jules            ###   ########.fr       */
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
		if (!ft_strncmp(cmd, builtin[i].str, ft_max(builtin[i].str, cmd) - 1))
		{
			printf("Command is "GREEN"%s\n"RESET, builtin[i].str);
			return (i);
		}
		i++;
	}
	if (i == sizeof(builtin) / sizeof(*builtin))
		printf(RED"%s : Command not found\n"RESET, cmd);
	return (-1);
}

void	ft_menu(t_command *cmd)
{
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		ft_echo(cmd);
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

void	exec_command(t_command *cmd, char **buffer)
{
	cmd->name = ft_strdup(buffer[0]);
	cmd->operation = ft_iscommand(cmd->name);
	ft_show_double(buffer);
	if (cmd->operation >= 0)
	{
		cmd->args = buffer + 1;
		cmd->args_cpy = buffer + 1;
		ft_show_double(cmd->args);
		ft_show_double(cmd->args_cpy);
		ft_menu(cmd);
	}
}
