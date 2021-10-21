/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/21 21:31:24 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int check_identifier(char *id)
{
    int i;

    i = 0;
    if (!id)
        return (-1);
    if (ft_isdigit(id[0]))
        return (-1);
    while (id[i])
    {
        if (!ft_isalnum(id[i]) && id[i] != '=')
            return (-1);
        i++;
    }
    return (1);
}


int check_variable(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            return (2);
        i++;
    }
    if (i == 0)
        return (-1);
    return (1);
}

int loop_identifier(char **args)
{
    while (args && *args)
    {
        if (check_identifier(*args) == -1)
            return (-1);
        if (check_variable(*args) == -1)
            return (-1);
        args++;
    }
    return (1);
}

void	ft_export(char **args, t_list *e)
{
    int flag;

    flag = 0;
    if (!*args)
    {
        flag = 1;
		print_env(e);
    }
    else if (!ft_strncmp(args[0], "-", 1))
    {
        ft_putstr_fd("export : invalid option\n", 1);
        flag = 1;
    }
    else if (loop_identifier(args) != 1 && flag == 0)
    {
        ft_putstr_fd("export : not valid in this context\n", 1);
        flag = 1;
    }
	while (args && *args && flag == 0)
	{
        ft_add_env(*args, e);
        args++;
    }
}