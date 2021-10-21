/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/21 20:53:35 by julpelle         ###   ########.fr       */
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

char    *create_var(char *variable, int opt)
{
    char    *res;

    if (opt == -1)
        res = ft_strjoin(variable, "=");
    else
        res = ft_strdup(variable);
    return (res);
}

void    export_variable(char *variable, t_list *e)
{
    char    *res;

    if (check_variable(variable) == 1)
    {
        res = create_var(variable, -1);
        ft_add_env(res, e);
    }
    else if (check_variable(variable) == 2)
    {
        res = create_var(variable, 2);
        ft_add_env(res, e);
    }
    free(res);
}

void	ft_export(char **args, t_list *e)
{
    int flag;

    flag = 0;
    if (!*args)
    {
        ft_putstr_fd("No args\n", 1);
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
        export_variable(*args, e);
        args++;
    }
}