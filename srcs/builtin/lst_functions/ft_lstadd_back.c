/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:36:13 by julpelle          #+#    #+#             */
/*   Updated: 2021/09/29 23:30:14 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *lst;

	lst = *alst;
	if (*alst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
	else
		*alst = new;
}

void	ft_lst_pushback(t_list **list, char *content)
{
	t_list	*lst;

	lst = *list;
	if (lst == NULL)
	{
		lst = ft_lstnew((void *)content);
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = ft_lstnew((void *)content);
}
