/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:47:25 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/03 21:35:16 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int	ft_unset(t_list *l, char **args)
{
	int	flag;

	flag = 0;
	while (*args)
	{
		if (!(**args))
			flag = print_custom("unset : not a valid identifier", 2, 1, 1);
		else
			ft_del_variable(*args, l);
		args++;
	}
	return (flag);
}
