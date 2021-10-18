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

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = content;
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
	list = list->next;
}

t_list	*ft_tab_to_lst(char *table[])
{
	t_list	*list;

	list = NULL;
	while (*table != NULL)
	{
		ft_lst_pushback(&list, *table);
		table++;
	}
	return (list);
}