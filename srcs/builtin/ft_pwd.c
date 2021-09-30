/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:36:59 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 18:05:43 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

void	ft_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(cmd->fd_out, pwd, ft_strlen(pwd));
	write(cmd->fd_out, "\n", 1);
} 