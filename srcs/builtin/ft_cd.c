/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:13 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 19:26:04 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

char	*add_apo_arg(char *ptr)
{
	char	*str;
	int		count;
	int		count2;

	str = malloc(ft_strlen(ptr) + 3);
	if (!str)
		return (NULL);
	count = 0;
	count2 = 0;
	str[count++] = '\"';
	while (ptr[count2])
		str[count++] = ptr[count2++];
	str[count++] = '\"';
	str[count] = 0;
	return (str);
}

void	ft_swap_env_pwd(char *arg, t_list *e)
{
	char	*ptr;
	char	*ptr2;

	ptr = custom_getenv(e, "PWD", 1);
	ft_del_variable("OLDPWD", e);
	ptr2 = ft_strjoin("OLDPWD=", ptr);
	free(ptr);
	ft_add_env(ptr2, e);
	free(ptr2);
	ft_del_variable("PWD", e);
	ptr = add_apo_arg(arg);
	ptr2 = ft_strjoin("PWD=", ptr);
	ft_add_env(ptr2, e);
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
	if (args)
	{
		if (args[0][ft_strlen(args[0]) - 1] == '/')
			args[0][ft_strlen(args[0]) - 1] = 0;
	}
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

int	check_path(t_list *l)
{
	char	*path;
	int		count;
	int		res;

	path = custom_getenv(l, "PWD", 0);
	count = 0;
	res = 0;
	while (path[count])
	{
		if (path[count] == '/')
			res++;
		count++;
	}
	free(path);
	return (res);
}

int	ft_cd(char **args, t_list *l)
{
	int		last_exit;
	char	**str;
	int		test;

	last_exit = 0;
	if (ft_strlen_double(args) > 1 )
	{
		print_custom("cd: too many arguments", 2, 1, 1);
		last_exit = 1;
	}
	else if (!args || !(*args) || (*args && *args[0] == '~'))
		ft_cd_noargs(l, &last_exit);
	else if (args[0][0] == '-')
		ft_cd_minus(args, l, &last_exit);
	else if (*args && args[0][0] == '.' && !args[0][1])
		;
	else if (args[0][0] == '.' && args[0][1] == '.')
	{
		str = malloc(sizeof(char *) * 2);
		ft_cd_back(args, l, &last_exit);
		test = check_path(l);
		if (args[0][2] && args[0][2] == '/' && args[0][3] && test > 0)
		{
			str[0] = &args[0][3];
			str[1] = 0;
			ft_cd(str, l);
		}
		if (test == 0)
			ft_swap_env_pwd("/", l);
		free(str);
	}
	else
		ft_cd_arg(args, l, &last_exit);
	return (last_exit);
}
