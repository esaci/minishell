/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:47:25 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/04 00:15:49 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int	ft_unset(t_list *l, char **args)
{
	int		flag;

	flag = 0;
	while (*args)
	{
		if (!(**args) || ft_strchr(*args, '='))
			flag = print_custom("unset : not a valid identifier", 2, 1, 1);
		else
			ft_del_variable(*args, l);
		args++;
	}
	return (flag);
}
