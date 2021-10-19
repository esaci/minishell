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

t_list	*ft_init_env(char *envp[], t_list *env)
{
	if (env)
		print_custom("pointeur non nul envoye a init_env", 2, 1, 1);
	return (ft_envp(envp, NULL, env));
}

t_list	*ft_add_env(char *to_add, t_list *env)
{
	if (!env)
		print_custom("pointeur nul envoye a add_env", 2, 1, 1);
	return (ft_envp(NULL, to_add, env));
}
