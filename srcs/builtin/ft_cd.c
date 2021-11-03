/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:42:13 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/04 00:41:41 by julpelle         ###   ########.fr       */
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

	(void)arg;
	ptr = custom_getenv(e, "PWD", 1);
	ft_del_variable("OLDPWD", e);
	ptr2 = ft_strjoin("OLDPWD=", ptr);
	free(ptr);
	ft_add_env(ptr2, e);
	free(ptr2);
	ft_del_variable("PWD", e);
	ptr = malloc(sizeof(char) * 1000);
	if (!ptr)
		return ;
	ptr = getcwd(ptr, 1000);
	ptr2 = add_apo_arg(ptr);
	free(ptr);
	ptr = ft_strjoin("PWD=", ptr2);
	ft_add_env(ptr, e);
	free(ptr);
	free(ptr2);
}

void	ft_cd_noargs(t_list *e, int *last_exit)
{
	char	*arg;
	char	*tmp;

	arg = custom_getenv(e, "HOME", 0);
	tmp = custom_getenv(e, "HOME", 1);
	if ((!arg || !arg[0]) && (!tmp || !tmp[0]))
	{
		ft_putstr_fd("Minishell : cd : HOME doesn't exist\n", 2);
		*last_exit = 1;
	}
	else if (!arg || !arg[0])
		*last_exit = 0;
	else if (chdir(arg) != 0)
		error_chdir(NULL, last_exit);
	else
		ft_swap_env_pwd(arg, e);
	free(arg);
	free(tmp);
}

int	ft_cd(char **args, t_list *l)
{
	int		last_exit;
	int		test;

	last_exit = 0;
	if (ft_strlen_double(args) > 1 )
	{
		print_custom("cd: too many arguments", 2, 1, 1);
		last_exit = 1;
	}
	else if (!args || !(*args) || (*args && *args[0] == '~'))
		ft_cd_noargs(l, &last_exit);
	else
	{
		test = chdir(*args);
		if (test != -1)
			ft_swap_env_pwd(*args, l);
		else
		{
			print_custom("cd : file does not exist", 2, 1, 1);
			error_chdir(*args, &last_exit);
		}
	}
	return (last_exit);
}
