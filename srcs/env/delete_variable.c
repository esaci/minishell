/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:27:01 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/21 19:01:13 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

t_list	*ft_del_variable(char *ptr, t_list *env)
{
	t_list	*prev;
	t_list	*tmp_e;

	prev = NULL;
	tmp_e = env;
	while (tmp_e)
	{
		if (tmp_e->content && !ft_memcmp(tmp_e->content, ptr, ft_strlen(ptr)))
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
				env->content = NULL;
				return(env);
			}
			return (env);
		}
		prev = tmp_e;
		tmp_e = tmp_e->next;
	}
	return (env);
}

t_list	*free_env(t_list *env)
{
	t_list	*tmp;

	while(env)
	{
		tmp = env;
		env = env->next;
		if (tmp->content)
			free(tmp->content);
		if (tmp)
			free(tmp);
	}
	return (NULL);
}