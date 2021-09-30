/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:17:01 by julpelle          #+#    #+#             */
/*   Updated: 2021/09/29 22:18:51 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!(lst))
		return ((t_list *)0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
