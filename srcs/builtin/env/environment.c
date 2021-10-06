/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:24:28 by Jules             #+#    #+#             */
/*   Updated: 2021/10/04 12:50:53 by julespellet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

t_list	**ft_envp(char *envp[], char *content, t_list *env)
{
	static t_list	*environment = NULL;

	printf("CHECK FT_ENVP : ");
	if (envp != NULL)
		environment = ft_tab_to_lst(envp);
	else if (content != NULL)
		ft_lst_pushback(&environment, content);
	else if (env != NULL)
		environment = env;
	if (environment != NULL)
		printf("OK OUFFFF \n");
	else
		printf("MERDEEEE \n");
	return (&environment);
}

char	*ft_getenv(char *key)
{
	t_list	*env;

	env = ft_getallenv();
	while (env)
	{
		if (ft_strlen(env->content) > ft_strlen(key))
		{
			if (ft_strncmp(env->content, key, ft_strlen(key)) == 0
				&& *(env->content + ft_strlen(key)) == '=')
				return (env->content + ft_strlen(key) + 1);
		}
		env = env->next;
	}
	return (NULL);
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