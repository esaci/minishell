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
	if (!arg || !arg[0])
		ft_putstr_fd("Minishell : cd : HOME doesn't exist\n", 2);
	else if (chdir(arg) != 0)
		error_chdir(NULL);
	else
		ft_swap_env_pwd(arg, e);
	free(arg);
}

void	ft_cd_arg(char **args, t_list *e)
{
	if (args && *args[0] == '/')
	{
		if (chdir(*args) != 0)
			error_chdir(*args);
		else
			ft_swap_env_pwd(*args, e);
	}
	else
		ft_cd_other(args, e);
}

void	ft_cd(char **args, t_list *l)
{
	if (ft_strlen_double(args) > 1)
		print_custom("cd: too many arguments", 2, 1, 1);
	else if (!args | !(*args))
		ft_cd_noargs(l);
	else if (args[0][0] == '-')
		ft_cd_minus(args, l);
	else
		ft_cd_arg(args, l);
}