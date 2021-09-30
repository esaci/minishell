/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:36:15 by Jules             #+#    #+#             */
/*   Updated: 2021/09/30 12:39:58 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

t_list	**ft_init_env(char *envp[])
{
	t_list	**env;
	
	env = NULL;
	printf("Test 1: %s\n", *envp);
	*env = ft_lstnew((void *)*envp);
	printf("Test 2: %s\n", (*env)->content);
	return (env);
}