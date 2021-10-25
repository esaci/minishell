/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:17:27 by elias             #+#    #+#             */
/*   Updated: 2021/10/22 15:17:29 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../lib/libmin_built.h"

void	ft_cd_minus(char **args, t_list *e)
{
	char	*path;
	
	if (!ft_strncmp(*args, "-", 2))
	{
		path = custom_getenv(e, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd : OLDPWD is not set\n", 2);
		if (chdir(path) != 0)
			error_chdir(*args);
		else
			ft_swap_env_pwd(path, e);
		if (path)
			free(path);
	}
	else
		ft_putstr_fd("Invalid option\n", 2);
}

void	ft_cd_other(char **args, t_list *e)
{
	char	*path;

	if (chdir(*args) != 0)
		error_chdir(*args);
	else
	{
		path = custom_getenv(e, "PATH");
		ft_swap_env_pwd(path, e);
		free(path);
	}
}

void	error_chdir(char *ptr)
{
	char	*tmp;

	tmp = merge_twoarray("Minishell: cd: ", ptr, 3);
	perror(tmp);
	free(tmp);
}