/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/23 01:22:06 by julpelle         ###   ########.fr       */
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
        if (!ft_isalnum(id[i]) && (id[i] != '=' && id[i] != '+'))
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

char    *get_var(char *arg)
{
    int     i;
    char    *res;

    i = 0;
    if (!arg)
        return (copieur(""));
    while (arg[i] && arg[i] != '=')
        i++;
    if (arg[i - 1] == '+')
        i--;
    res = ft_substr(arg, 0, i);
    return (res);
}

char    *get_value(char *arg)
{
    int     i;

    i = 0;
    while (arg[i] != '=')
        i++;
    return (&arg[i + 1]);
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

void    export_cases(char *arg, t_list *e)
{
    char    *var;
    char    *ptr;
    char    *ptr2;
    char    *ptr3;
    char    *ptr4;

    var = get_var(arg);
    ptr = custom_getenv(e, arg);
/*     printf("VAR : %s\n", var);
    printf("PTR : %s\n", ptr); */
    ft_del_variable(var, e);
    if (check_variable(arg) == 1)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, ptr);
        ptr4 = ft_strjoin(ptr3, get_value(arg));
        ft_add_env(ptr4, e);
        free(ptr2);
        free(ptr3);
        free(ptr4);
    }
    else if (check_variable(arg) == 2)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, "\"");
        ptr4 = ft_strjoin(ptr3, get_value(arg));
        free(ptr2);
        ptr2 = ft_strjoin(ptr4, "\"");
        ft_add_env(ptr2, e);
        free(ptr2);
        free(ptr3);
        free(ptr4);
    }
    else if (check_variable(arg) == 3)
        ft_add_env(arg, e);
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
        export_cases(*args, e);
        args++;
    }
}