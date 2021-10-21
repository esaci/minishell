/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:38 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 20:04:51 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

char    *str_low(char *str)
{
    char    *res;
    int     i;

    i = 0;
    if (!str)
        return (NULL);
    res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
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
    res[i] = '\0';
    return (res);
}

int is_command(char *command, char **args, char **envp, t_lexer *l)
{
    if (!ft_strncmp(command, "echo", 5))
    {
        ft_echo(command);
        exit(0);
    }
    if (!ft_strncmp(command, "env", 4))
    {
        ft_env(l->envp);
        exit(0);
    }
    if (!ft_strncmp(command, "pwd", 4))
    {
        ft_pwd(command);
        small_free(l, NULL, NULL, 0);
        exit(0);
    }
    if (!ft_strncmp(command, "unset", 6))
    {
        ft_unset(l->envp, **args);
        exit(0);
    }
    if (!ft_strncmp(command, "cd", 3))
    {
        ft_cd(command, args, envp);
        exit(0);
    }
    if (!ft_strncmp(command, "export", 7))
    {
        ft_export(command, args, envp);
        exit(0);
    }
    free(command);
    return (0);
}

int menu(char *command, char **args, char **envp, t_lexer *l)
{
    is_command(command, args, envp, l);
    return (0);
}