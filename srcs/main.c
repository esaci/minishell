/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:34:34 by esaci             #+#    #+#             */
/*   Updated: 2021/10/18 20:15:06 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	main(int ac, char *av[], char *envp[])
{
	void	(*sigint_c)(int);

	if (envp[0] == NULL)
		return (print_custom("Manque Envp\n", 2, 1, 1));
	//ft_init_env(envp);
	sigint_c = sig_handler();
	start_fonction(envp);
	return (0);
	sigint_c(av[ac - 1][0]);
	free_list(ft_getallenv());
	return (0);
}
