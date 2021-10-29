/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:55:01 by julespellet       #+#    #+#             */
/*   Updated: 2021/10/18 20:08:06 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

t_list	*ft_new_list_elem(char *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list) * 2);
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = copieur(content);
	return (new);
}

void	ft_lst_pushback(t_list **lst, char *content)
{
	t_list	*list;

	list = *lst;
	if (list == NULL)
	{
		*lst = ft_new_list_elem(content);
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = ft_new_list_elem(content);
}

t_list	*ft_tab_to_lst(char *envp[])
{
	t_list	*list;
	char	*ptr;

	list = NULL;
	while (envp && *envp != NULL)
	{
		ptr = add_apo_envp(*envp);
		ft_lst_pushback(&list, ptr);
		free(ptr);
		envp++;
	}
	return (list);
}

int	utils_strlen_env(t_list *l)
{
	int	count;

	count = 0;
	while (l)
	{
		l = l->next;
		count++;
	}
	return (count);
}

int print_env(t_list *env)
{
    while (env)
    {
        ft_putstr_fd(env->content, 1);
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
    return (0);
}