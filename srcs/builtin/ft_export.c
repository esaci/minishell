/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:19:14 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:31:31 by julpelle         ###   ########.fr       */
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
        if (!ft_isalnum(id[i]))
            return (-1);
        i++;
    }
    return (1);
}

char    **ft_create_var(char **args)
{
    char    *line;
    char    **arg;
    int     i;

    i = 0;
    line = *args;
    arg = (char **)malloc(sizeof(char *) * 4);
    arg[3] = NULL;
    while (line[i] && (line[i] != '=' || line[0] == '='))
        i++;
    arg[0] = ft_substr(line, 0, i);
    if (line[i] && line[i] == '=')
        arg[1] = ft_strdup("=");
    if (line[i])
        arg[2] = ft_strdup(line + i);
    return (arg);
}

int ft_print_env()
{
    t_list  *env;

    env = ft_getallenv();
    while (env)
    {
        ft_putstr_fd(env->content, 1);
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
    return (0);
}

int export_variable(char **args)
{
    int     ret;
    char    **arg;

    while(*args)
    {
        arg = ft_create_var(args);
        if (!check_identifier(arg[0]))
        {
            ft_putstr_fd("bash : not a valid identifier\n", 1);
            ret = 1;
        }
        else
        {
            if (arg[1])
                ft_del_variable(arg[0]);
            ft_add_env(ft_strdup(*args));
            ret = 0;
        }
        args++;
    }
    free(arg);
    return (ret);
}

void    ft_export(char *command, char **args, char **envp)
{
    int ret;

    ret = 0;
    (void)command;
    (void)envp;
    if (*args)
    {
        if (*args[0] == '-')
        {
            ft_putstr_fd("export : invalid option\n", 1);
            ret = 1;
        }
        else
            ret = export_variable(args);
    }
    else
        ret = ft_print_env();
    (void)ret;
    exit(0);
}