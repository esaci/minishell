/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:55:24 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 18:45:19 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"
int ft_check_echo(char *flag)
{
    int i;
    int count;

    i = 0;
    count = 0;
    printf("CHECK\n");
    if (!flag)
        return (-1);
    while (flag[i++] == '-')
        count++;
    if (count != 1)
        return (-1);
    if (flag[count] == 'n')
        return (1);
    return (-1);    
}

void    ft_echo(char *command, char **args, char **envp)
{
    int flag;

    flag = 0;
    (void)envp;
    printf("Command : %s\n", command);
    if (ft_check_echo(args[0]) == 1 && args[1])
    {
        printf(GREEN"Flag is ok\n"RESET);
        flag = 1;
        (args)++;
    }
    else
        printf(RED"Flag is not ok\n"RESET);
    while (*args)
    {
        if (ft_strncmp(*args, "\0", 1))
            ft_putstr_fd(*args, 1);
        (args)++;
        if (*args)
            ft_putstr_fd(" ", 1);
    }
    if (flag == 0)
        ft_putstr_fd("\n", 1);
}