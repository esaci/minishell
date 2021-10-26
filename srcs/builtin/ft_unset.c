/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:47:25 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 19:28:57 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int	ft_unset(t_list *l, char **args)
{
	while(*args)
	{
		ft_del_variable(*args, l);
		args++;
	}
	return (0);
}