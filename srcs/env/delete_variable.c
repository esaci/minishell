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
t_list	*ft_del_variable(char *variable, t_list *env)
{
	t_list	*prev;
	t_list	*tmp_e;

	prev = NULL;
	tmp_e = env;
	while (tmp_e)
	{
		if (ft_strlen(tmp_e->content) > ft_strlen(variable))
		{
			if (ft_strncmp(tmp_e->content, variable, ft_strlen(variable)) == 0
				&& *(tmp_e->content + ft_strlen(variable)) == '=')
			{
				if (prev)
				{
					prev->next = tmp_e->next;
					free(tmp_e->content);
					free(tmp_e);
				}
				else
				{
					free(env->content);
					free(env);
					return(tmp_e->next);
				}
				return (env);
			}
		}
		prev = tmp_e;
		tmp_e = tmp_e->next;
	}
	return (env);
}