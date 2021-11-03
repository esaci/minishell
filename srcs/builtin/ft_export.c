/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/03 21:28:02 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

char	*get_var(char *arg)
{
	int		i;
	char	*res;

	i = 0;
	if (!arg)
		return (copieur(""));
	while (arg[i] && arg[i] != '=')
		i++;
	if (i && arg[i - 1] && arg[i - 1] == '+')
		i--;
	res = ft_substr(arg, 0, i);
	return (res);
}

char	*get_value(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == (int)ft_strlen(arg))
		return (arg);
	return (&arg[i + 1]);
}

int	loop_identifier_mini(char **args)
{
	if (loop_identifier(args) != 1)
	{
		ft_putstr_fd("export : not valid in this context\n", 1);
		return (1);
	}
	return (0);
}

int	ft_export(char **args, t_list *e, int flag)
{
	int		flag2;

	flag2 = 0;
	if (!*args)
	{
		flag = 1;
		print_env(e);
	}
	else if (!ft_strncmp(args[0], "-", 1))
	{
		ft_putstr_fd("export : invalid option\n", 1);
		args++;
		flag2 = 1;
	}
	while (args && *args && flag == 0)
	{
		flag2 += loop_identifier_mini(args);
		if (flag2 != 1)
			export_cases(*args, e);
		args++;
	}
	if (flag2)
		return (1);
	return (0);
}
