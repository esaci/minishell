/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:13 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:51:27 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	ft_swap_env_pwd(char *arg, t_list *e)
{
	char	*ptr;
	char	*ptr2;

	ptr = custom_getenv(e, "PWD");
	ft_del_variable("OLDPWD", e);
	ptr2 = ft_strjoin("OLDPWD=", ptr);
	ft_add_env(ptr2, e);
	free(ptr2);
	free(ptr);
	ft_del_variable("PWD", e);
	ptr2 = ft_strjoin("PWD=", arg);
	ft_add_env(ptr2, e);
	free(ptr2);
}

void	ft_cd_noargs(t_list *e)
{
	char	*arg;

	arg = custom_getenv(e, "HOME");
	if (!arg)
		ft_putstr_fd("cd : HOME doesn't exist\n", 1);
	else if (chdir(arg) != 0)
		ft_putstr_fd("cd : no such file or directory\n", 1);
	else
		ft_swap_env_pwd(arg, e);
	free(arg);
}

void	ft_cd_minus(char **args, t_list *e)
{
	char	*path;
	
	if (!ft_strncmp(*args, "-", 2))
	{
		path = custom_getenv(e, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd : OLDPWD is not set\n", 1);
		if (chdir(path) != 0)
			ft_putstr_fd("cd : no such file or directory\n", 1);
		else
			ft_swap_env_pwd(path, e);
	}
	else
		ft_putstr_fd("Invalid option\n", 1);
}

void	ft_cd_other(char **args, t_list *e)
{
	char	*path;

	if (chdir(*args) != 0)
		ft_putstr_fd("cd : error\n", 1);
	else
	{
		path = custom_getenv(e, "PATH");
		ft_swap_env_pwd(path, e);
		free(path);
	}
}

void	ft_cd_arg(char **args, t_list *e)
{
	if (args && *args[0] == '/')
	{
		if (chdir(*args) != 0)
			ft_putstr_fd("cd : error\n", 1);
		else
			ft_swap_env_pwd(*args, e);
	}
	else
		ft_cd_other(args, e);
}

void	ft_cd(char **args, t_list *l)
{
	if (!args | !(*args))
		ft_cd_noargs(l);
	else
		ft_cd_arg(args, l);
}