/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/27 16:11:46 by julpelle         ###   ########.fr       */
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

void    export_cases(char *arg, t_list *e)
{
    char    *var;
    char    *ptr;
    char    *ptr2;
    char    *ptr3;
    char    *ptr4;
    char    *old_value;
    char    *test;
    char    *test2;
    int     flag;

    flag = 0;
    var = get_var(arg);
    ptr = custom_getenv(e, arg);
    test = custom_getenv(e, var);
    old_value = get_value(arg);
    ft_del_variable(var, e);
    if (check_all_char(old_value) == 1 && ft_strncmp(ptr, "", 1))
        flag = 1;
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
        ptr2 = ft_strjoin(var, "=\"");
        test2 = ft_substr(test, 1, ft_strlen(test) - 2);
        ptr3 = ft_strjoin(ptr2, test2);
        free(test2);
        ptr4 = ft_strjoin(ptr3, ptr);
        free(ptr2);
        ptr2 = ft_strjoin(ptr4, get_value(arg));
        free(ptr3);
        ptr3 = ft_strjoin(ptr2, "\"");
        ft_add_env(ptr3, e);
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
    free(var);
    free(ptr);
    free(test);
}

int ft_export(char **args, t_list *e)
{
    int flag;
    int	flag2;

    flag = 0;
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
	/*
    else if (loop_identifier(args) != 1 && flag == 0)
    {
        ft_putstr_fd("export : not valid in this context\n", 1);
		flag2 = 1;
    }
	*/
    while (args && *args && flag == 0)
    {
		if (loop_identifier(args) != 1 && flag == 0)
			flag = 1;
		else
        	export_cases(*args, e);
        args++;
    }
    return (flag2);
}