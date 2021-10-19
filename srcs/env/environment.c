/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:24:28 by Jules             #+#    #+#             */
/*   Updated: 2021/10/18 18:45:19 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

t_list	*ft_envp(char *envp[], char *content, t_list *v_env)
{
	if (envp != NULL && !v_env)
		v_env = ft_tab_to_lst(envp);
	else if (content != NULL && v_env)
		ft_lst_pushback(&v_env, content);
	return (v_env);
}