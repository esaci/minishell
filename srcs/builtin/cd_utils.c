/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:17:27 by elias             #+#    #+#             */
/*   Updated: 2021/10/28 17:15:07 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

#include "../../lib/libmin_built.h"

int	ft_cd_minus(char **args, t_list *e, int *last_exit)
{
	char	*path;
	
	if (!ft_strncmp(*args, "-", 2))
	{
		path = custom_getenv(e, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd : OLDPWD is not set\n", 2);
		if (chdir(path) != 0)
			error_chdir(*args, last_exit);
		else
			ft_swap_env_pwd(path, e);
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
	char	*path;
	char	*ptr;
	char	*ptr2;

	if (chdir(*args) != 0)
		error_chdir(*args, last_exit);
	ptr = custom_getenv(e, "PWD");
	ptr2 = ft_strjoin(ptr, *args);
	printf("PTR2 : %s\n", ptr2);
	if (chdir(ptr2) == 0)
		ft_swap_env_pwd(ptr2, e);
	else
	{
		path = custom_getenv(e, "PATH");
		ft_swap_env_pwd(path, e);
		free(path);
	}
	return (0);
}

void	ft_cd_back(char **args, t_list *e, int *last_exit)
{
	char	*ptr;
	int		i;
	char	*ptr2;

	(void)args;
	(void)last_exit;
	ptr = custom_getenv(e, "PWD");
	i = ft_strlen(ptr) - 1;
	while (ptr[i] && ptr[i] != '/')
		i--;
	ptr2 = ft_substr(ptr, 0, i);
	free(ptr);
	printf("ptr2 : %s\n", ptr2);
	ft_swap_env_pwd(ptr2, e);
	free(ptr2);
}

void	error_chdir(char *ptr, int	*last_exit)
{
	char	*tmp;

	tmp = merge_twoarray("Minishell: cd: ", ptr, 3);
	perror(tmp);
	free(tmp);
	*last_exit = 1;
}