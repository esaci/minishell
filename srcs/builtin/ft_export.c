/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/24 23:07:41 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

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
    if (!arg)
        return (NULL);
    while (arg[i] && arg[i] != '=')
        i++;
    if (i == (int)ft_strlen(arg))
        return (arg);    
    return (&arg[i + 1]);
}

/*
char    *extra_export(char *arg, char *ptr, int case, char *var)
{
    char    *ptr2;
    char    *ptr3;
    char    *ptr4;

    if (case == 0)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, ptr);
        free(ptr2);
        return (ptr3);
    }
    if (case == 1)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, ptr);
        ptr4 = ft_strjoin(ptr3, get_value(arg));
        free(ptr2);
        free(ptr3);
        return (ptr4);
    }
    if (case == 2)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, "\"");
        ptr4 = ft_strjoin(ptr3, get_value(arg));
        free(ptr2);
        free(ptr3);
        ptr2 = ft_strjoin(ptr4, "\"");
        free(ptr4);
        return (ptr2);
    }
    return (res);
}
*/

void    export_cases(char *arg, t_list *e)
{
    char    *var;
    char    *ptr;
    char    *ptr2;
    char    *ptr3;
    char    *ptr4;
    int     flag;

    flag = 0;
    var = get_var(arg);
    ptr = custom_getenv(e, arg);
    ptr2 = get_value(arg);
    ft_del_variable(var, e);
    if (check_all_char(ptr2) == 1 && ft_strncmp(ptr, "", 1))
        flag = 1;
    ptr2 = NULL;
    if (flag == 1)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, ptr);
        ft_add_env(ptr3, e);
        free(ptr2);
        free(ptr3);
    }
    ptr2 = NULL;
    if (check_variable(arg) == 1 && flag == 0)
    {
        ptr2 = ft_strjoin(var, "=");
        ptr3 = ft_strjoin(ptr2, ptr);
        ptr4 = ft_strjoin(ptr3, get_value(arg));
        ft_add_env(ptr4, e);
        free(ptr2);
        free(ptr3);
        free(ptr4);
    }
    else if (check_variable(arg) == 2 && flag == 0)
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
    else if (check_variable(arg) == 3 && flag == 0)
    {
        ft_add_env(arg, e);
    }
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