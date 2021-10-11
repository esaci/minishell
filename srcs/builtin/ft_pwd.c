/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:36:59 by Jules             #+#    #+#             */
/*   Updated: 2021/10/06 14:46:47 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

void	ft_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(cmd->fd_out, pwd, ft_strlen(pwd));
	write(cmd->fd_out, "\n", 2);
} 