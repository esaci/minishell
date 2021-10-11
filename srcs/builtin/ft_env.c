/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:55:51 by Jules             #+#    #+#             */
/*   Updated: 2021/10/06 13:20:58 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

void	ft_env(t_command *cmd)
{
	t_list	*env;
	
	env = ft_getallenv();
	while (env)
	{
		if (ft_strchr(env->content, '='))
		{
			write(cmd->fd_out, env->content, ft_strlen(env->content));
			write(cmd->fd_out, "\n", 2);
		}
		env = env->next;
	}
}