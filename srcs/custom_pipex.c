/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 23:17:45 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 23:17:46 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

void	init_pip(t_pip *pip, int value)
{
	pip->b_ac = value; //juste pour pa erreur
}

int	pipex_custom(int value, char *envp[])
{
	t_pip pip;

	init_pip(&pip, value);
	return (0);
	if (envp[0])
		return (0);
}
