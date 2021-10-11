/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:05:52 by Jules             #+#    #+#             */
/*   Updated: 2021/10/06 14:48:09 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

void	change_pwd(char *path)
{
	ft_delete_variable("OLDPWD");
	printf("NEW OLD PWD : %s\n", ft_strjoin("OLDPWD=", getenv("PWD")));
	ft_add_env(ft_strjoin("OLDPWD=", getenv("PWD")));
	ft_delete_variable("PWD");
	printf("NEW PWD : %s\n", ft_strjoin("PWD=", path));
	ft_add_env(ft_strjoin("PWD=", path));
}

void	ft_cd_noargs(void)
{
	char	*path;

	path = getenv("HOME");
	printf("Path : %s\n", path);
	if (!path)
		write(ERROR_INPUT, "HOME doesn't exist !\n", 22);
	else
		change_pwd(path);
}

void	ft_cd(t_command *cmd)
{
	printf("Commande : %s\n", cmd->args[0]);
	printf("Commande 2 : %s\n", cmd->args[1]);
	if (ft_strncmp(cmd->args[1], "\n", 2) == 0)
		ft_cd_noargs();
	else
		printf(RED"Not done yet\n"RESET);
}