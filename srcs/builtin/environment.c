/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:24:28 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 23:32:15 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lib_jules.h"

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

t_list	**ft_envp(char *envp[], char *content, t_list *env)
{
	static t_list	*environment;

	environment = NULL;
	if (envp != NULL)
		environment = convert_tab_list(envp);
	else if (content != NULL)
		ft_lst_pushback(&environment, content);
	else if (env != NULL)
		environment = env;
	return (&environment);
}

/*
void	get_environment(char *str)
{
	
}
*/