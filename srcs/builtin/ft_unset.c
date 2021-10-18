/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:47:25 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:28:57 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"
void    ft_unset(char *command, char **args)
{
    (void)command;
    while(*args)
    {
        ft_del_variable(*args);
        ft_env("env");
        args++;
    }
}