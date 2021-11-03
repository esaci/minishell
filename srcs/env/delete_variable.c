/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:27:01 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/03 02:46:04 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

t_list	*ft_del_variable_suite(char *ptr, t_list *env, \
	t_list *prev, t_list *tmp_e)
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
			return (env);
		}
		return (env);
	}
	return (NULL);
}

t_list	*ft_del_variable(char *ptr, t_list *env)
{
	t_list	*prev;
	t_list	*tmp_e;
	t_list	*tmp;

	prev = NULL;
	tmp_e = env;
	while (tmp_e)
	{
		tmp = ft_del_variable_suite(ptr, env, prev, tmp_e);
		if (tmp)
			return (tmp);
		prev = tmp_e;
		tmp_e = tmp_e->next;
	}
	return (env);
}

int	free_env(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->content)
			free(tmp->content);
		if (tmp)
			free(tmp);
	}
	return (1);
}

char	*add_apo_envp(char *env)
{
	char	*ptr;
	int		count;
	int		count2;

	ptr = malloc(sizeof(char) * (ft_strlen(env) + 3));
	if (!ptr)
		return (NULL);
	count = 0;
	count2 = 0;
	while (env && env[count] && env[count] != '=')
		ptr[count2++] = env[count++];
	if (!env[count])
	{
		ptr[count] = 0;
		return (ptr);
	}
	ptr[count2++] = env[count++];
	ptr[count2++] = '\"';
	while (env && env[count])
		ptr[count2++] = env[count++];
	ptr[count2++] = '\"';
	ptr[count2] = 0;
	return (ptr);
}
