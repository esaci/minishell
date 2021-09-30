/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 23:21:07 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 23:33:06 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

void	ft_lst_show(t_list *list)
{
	while(list->content)
	{
		if (list->content)
			printf("Content : %s\n", list->content);
		list = list->next;
	}
}