/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:55:24 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/23 00:08:53 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int ft_check_echo(char *flag)
{
    int i;
    int count;

    i = 0;
    count = 0;
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

void	ft_echo(char **args, int last_exit)
{
    int flag;

    flag = 0;
    if (ft_check_echo(args[0]) == 1 && args[1])
    {
        flag = 1;
        (args)++;
    }
    while (*args)
    {
        if (!ft_strncmp(*args, "$?", 2))
            ft_putnbr_fd(last_exit, 1);
        else if (ft_strncmp(*args, "\0", 1))
            ft_putstr_fd(*args, 1);
        (args)++;
        if (*args)
            ft_putstr_fd(" ", 1);
    }
    if (flag == 0)
        ft_putstr_fd("\n", 1);
}