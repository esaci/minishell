/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:51:11 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/30 11:53:55 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	ft_env(t_list *env)
{
	while (env)
	{
		if (ft_strchr(env->content, '='))
		{
			write(1, env->content, ft_strlen(env->content));
			write(1, "\n", 1);
		}
		env = env->next;
	}
}
