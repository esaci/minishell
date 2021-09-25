/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:34:34 by esaci             #+#    #+#             */
/*   Updated: 2021/09/24 15:34:50 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	main(int ac, char *av[], char *envp[])
{
	void	(*sigint_c)(int);

	if (envp[0] == NULL)
		return (print_custom("Manque Envp\n", 2, 1, 1));
	sigint_c = sig_handler();
	start_fonction(envp);
	return (0);
	return (av[ac - 1][0]);
}
