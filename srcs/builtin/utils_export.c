/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 22:46:34 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/27 16:16:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

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
        if (!ft_isalnum(id[i]) && (id[i] != '=' && id[i] != '+' && id[i] != '-'))
            return (-1);
        i++;
    }
    return (1);
}

int check_variable(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '+')
        {
            if (str[i + 1] == '=')
                return (1);
            else
                return (-1);
        }
        if (str[i] == '=')
            return (2);
        if (!ft_isalnum(str[i]))
            return (-1);
        i++;
    }
    return (3);
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

int check_existing(char *arg, t_list *e)
{
    char    *var;
    char    *ptr;

    var = get_var(arg);
    ptr = custom_getenv(e, var);
    if (ptr[0])
        return (1);
    ft_del_variable(ptr, e);
    return (0);
}

int check_all_char(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return (-1);
    while (arg[i])
    {
        if (!ft_isalpha(arg[i]))
            return (-1);
        i++;
    }
    return (1);
}