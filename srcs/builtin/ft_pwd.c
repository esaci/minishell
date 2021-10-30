/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:42:20 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/30 11:56:32 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	ft_pwd(t_list *l)
{
	char	*pwd;

	pwd = custom_getenv(l, "PWD", 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 2);
	free(pwd);
}
