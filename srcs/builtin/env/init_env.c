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

void	init_env(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	ft_envp(envp, NULL, NULL);
}

t_list	*ft_envgetall(void)
{
	return (*ft_envp(NULL, NULL, NULL));
}

void	add_env_variable(char *var)
{
	ft_envp(NULL, var, NULL);
}

t_list	**ft_get_env_var(void)
{
	return (ft_envp(NULL, NULL, NULL));
}