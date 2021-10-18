/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:38 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:03:25 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

char    *str_low(char *str)
{
    char    *res;
    int     i;

    res = malloc(sizeof(char) * ft_strlen(str));
    i = 0;
    while (str[i])
    {
        if (ft_isalpha(str[i]))
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                res[i] = str[i] + 32;
            else
                res[i] = str[i];
        }
        i++;
    }
    return (res);
}

int is_command(char *command, char **args, char **envp)
{
    if (!ft_strncmp(str_low(command), "echo", 5))
    {
        printf(GREEN"ECHO \n"RESET);
        ft_echo(command, args, envp);
        return (1);
    }
    if (!ft_strncmp(str_low(command), "env", 4))
    {
        printf(GREEN"ENV \n"RESET);
        ft_env(command);
        return (1);
    }
    if (!ft_strncmp(str_low(command), "pwd", 4))
    {
        printf(GREEN"PWD \n"RESET);
        ft_pwd(command);
        return (1);
    }
    if (!ft_strncmp(str_low(command), "unset", 6))
    {
        printf(GREEN"UNSET \n"RESET);
        ft_unset(command, args);
        return (1);
    }
    if (!ft_strncmp(str_low(command), "cd", 3))
    {
        printf(GREEN"CD \n"RESET);
        ft_cd(command, args, envp);
        return (1);
    }
    if (!ft_strncmp(str_low(command), "export", 7))
    {
        printf(GREEN"EXPORT \n"RESET);
        ft_export(command, args, envp);
        return (1);
    }
    return (0);
}

int menu(char *command, char **args, char **envp)
{
    (void)args;
    (void)envp;
    if (!is_command(command, args, envp))
        printf("ERROR COMMAND \n");
    return (0);
}