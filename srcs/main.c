/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:34:34 by esaci             #+#    #+#             */
/*   Updated: 2021/10/22 23:49:47 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

void	init_path_pwd(t_lexer *l, int mode)
{
	t_list	*c_envp;
	char	*ptr;

	c_envp = l->envp;
	if (mode)
	{
		if (l->pathptr)
			double_free(l->pathptr);
		if (l->pwd)
			double_free(l->pwd);
	}
	ptr = custom_getenv(c_envp, "PATH");
	l->pathptr = ft_split(ptr, ':');
	free(ptr);
	ptr = custom_getenv(c_envp, "PWD");
	l->pwd = ft_split(ptr, 1);
	free(ptr);
}
int	main(int ac, char *av[], char *envp[])
{
	void	(*sigint_c)(int);
	t_list	*c_envp;

	c_envp = ft_init_env(envp, NULL);
	sigint_c = sig_handler();
	start_fonction(c_envp);
	return (0);
	sigint_c(av[ac - 1][0]);
	return (0);
}
