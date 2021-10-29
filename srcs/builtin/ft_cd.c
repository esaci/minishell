/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:13 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/28 17:14:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	ft_swap_env_pwd(char *arg, t_list *e)
{
	char	*ptr;
	char	*ptr2;

	ptr = custom_getenv(e, "PWD", 1);
	ft_del_variable("OLDPWD", e);
	ptr2 = ft_strjoin("OLDPWD=", ptr);
	ft_add_env(ptr2, e);
	free(ptr2);
	free(ptr);
	ft_del_variable("PWD", e);
	ptr = ft_strjoin("PWD=", "\"");
	ptr2 = ft_strjoin(ptr, arg);
	free(ptr);
	ptr = ft_strjoin(ptr2, "\"");
	ft_add_env(ptr, e);
	free(ptr);
	free(ptr2);
}

void	ft_cd_noargs(t_list *e, int *last_exit)
{
	char	*arg;

	arg = custom_getenv(e, "HOME", 0);
	if (!arg || !arg[0])
	{
		ft_putstr_fd("Minishell : cd : HOME doesn't exist\n", 2);
		*last_exit = 1;
	}
	else if (chdir(arg) != 0)
		error_chdir(NULL, last_exit);
	else
		ft_swap_env_pwd(arg, e);
	free(arg);
}

void	ft_cd_arg(char **args, t_list *e, int *last_exit)
{
	if (args && *args[0] == '/')
	{
		if (chdir(*args) != 0)
			error_chdir(*args, last_exit);
		else
			ft_swap_env_pwd(*args, e);
	}
	else
		ft_cd_other(args, e, last_exit);
}

int	ft_cd(char **args, t_list *l)
{
	int	last_exit;

	last_exit = 0;
	if (ft_strlen_double(args) > 1)
	{
		print_custom("cd: too many arguments", 2, 1, 1);
		last_exit = 1;
	}
	else if (!args || !(*args) || (*args && *args[0] == '~'))
		ft_cd_noargs(l, &last_exit);
	else if (args[0][0] == '-')
		ft_cd_minus(args, l, &last_exit);
	else if (args[0][0] == '.' && !args[0][1])
		;
	else if (args[0][0] == '.' && args[0][1] == '.' && !args[0][2])
		ft_cd_back(args, l, &last_exit);
	else
		ft_cd_arg(args, l, &last_exit);
	return (last_exit);
}