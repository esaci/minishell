/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:27:01 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:29:13 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"
void	ft_del_variable(char *variable)
{
	t_list	*prev;
	t_list	*env;

	env = ft_getallenv();
	prev = NULL;
	while (env)
	{
		if (ft_strlen(env->content) > ft_strlen(variable))
		{
			if (ft_strncmp(env->content, variable, ft_strlen(variable)) == 0
				&& *(env->content + ft_strlen(variable)) == '=')
			{
				if (prev)
					prev->next = env->next;
				else
					ft_envp(NULL, NULL, env->next);
				return ;
			}
		}
		prev = env;
		env = env->next;
	}
	return ;
}