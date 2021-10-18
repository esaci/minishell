/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:36:15 by Jules             #+#    #+#             */
/*   Updated: 2021/10/18 19:37:26 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	ft_init_env(char *envp[])
{
	ft_envp(envp, NULL, NULL);
}

void	ft_add_env(char *to_add)
{
	ft_envp(NULL, to_add, NULL);
}

t_list	**ft_getaddenv(void)
{
	return (ft_envp(NULL, NULL, NULL));
}

t_list	*ft_getallenv(void)
{
	return (*ft_envp(NULL, NULL, NULL));
}