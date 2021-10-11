/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:24:28 by Jules             #+#    #+#             */
/*   Updated: 2021/10/06 14:48:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

t_list	**ft_envp(char *envp[], char *content, t_list *env)
{
	static t_list	*environment = NULL;

	if (envp != NULL)
		environment = ft_tab_to_lst(envp);
	else if (content != NULL)
		ft_lst_pushback(&environment, content);
	else if (env != NULL)
		environment = env;
	return (&environment);
}

/*
char	*get_environment(char *str)
{
	t_list	*env;

	env = ft_envgetall();
	while (env)
	{
		if (ft_strlen(env->content) > ft_strlen(str))
		{
			if (ft_strncmp(env->content, str, ft_strlen(str) == 0)
				&& *(env->content) + ft_strlen(str) == '=')
				return (env->content + ft_strlen(str) + 1);
		}
		env = env->next;
	}
	return (NULL);
}


t_list	*convert_tab_list(char *table[])
{
	t_list	*list;
	int	i;

	list = NULL;
	i = 0;
	while (table[i] != NULL)
	{
		ft_lst_pushback(&list, table[i]);
		i++;
	}
	return (list);
}

*/