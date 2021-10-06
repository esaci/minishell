/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:55:51 by Jules             #+#    #+#             */
/*   Updated: 2021/10/04 12:33:43 by julespellet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

/*
t_list	**ft_init_env(char *envp[])
{
	t_list	**env;
	
	env = NULL;
	printf("Test 1: %s\n", *envp);
	*env = ft_lstnew((void *)*envp);
	printf("Test 2: %s\n", (*env)->content);
	return (env);
}

void	fill_env(char *envp[])
{
	t_list	*env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	printf("I : %d\n", i);
	env = (t_list *)malloc(sizeof(t_list) * (i + 1));
	i = 0;
	while (envp[i])
	{
		printf("ENVP[%d] \t\t: %s\n", i, envp[i]);
		env->content = ft_strdup(envp[i]);
		printf("Content[%d] \t\t: %s\n", i, envp[i]);
		env = env->next;
		i++;
	}
}
*/

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