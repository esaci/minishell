/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:17:27 by elias             #+#    #+#             */
/*   Updated: 2021/11/02 19:24:15 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int	ft_cd_minus(char **args, t_list *e, int *last_exit)
{
	char	*path;

	if (!ft_strncmp(*args, "-", 2))
	{
		path = custom_getenv(e, "OLDPWD", 0);
		if (!path)
			ft_putstr_fd("cd : OLDPWD is not set\n", 2);
		if (chdir(path) != 0)
			error_chdir(*args, last_exit);
		else
		{
			free(path);
			path = custom_getenv(e, "OLDPWD", 1);
			ft_swap_env_pwd(path, e);
		}
		if (path)
			free(path);
	}
	else
	{
		ft_putstr_fd("Invalid option\n", 2);
		*last_exit = 1;
	}
	return (0);
}

int	ft_cd_other(char **args, t_list *e, int *last_exit)
{
	char	*ptr;
	char	*ptr2;
	int		x;

	x = chdir(*args);
	if (x)
		error_chdir(*args, last_exit);
	ptr = custom_getenv(e, "PWD", 0);
	ptr2 = ft_strjoin(ptr, "/");
	free(ptr);
	ptr = ft_strjoin(ptr2, *args);
	if (!x)
		ft_swap_env_pwd(ptr, e);
	free(ptr2);
	free(ptr);
	return (0);
}

void	ft_cd_back(char **args, t_list *e, int *last_exit)
{
	char	*ptr;
	int		i;

	(void)args;
	(void)last_exit;
	ptr = custom_getenv(e, "PWD", 0);
	i = ft_strlen(ptr) - 1;
	while (ptr[i] && ptr[i] != '/')
		i--;
	ptr[i] = 0;
	chdir(ptr);
	ft_swap_env_pwd(ptr, e);
	free(ptr);
}

void	error_chdir(char *ptr, int	*last_exit)
{
	char	*tmp;

	tmp = merge_twoarray("Minishell: cd: ", ptr, 3);
	perror(tmp);
	free(tmp);
	*last_exit = 1;
}
