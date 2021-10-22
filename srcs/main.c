/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:34:34 by esaci             #+#    #+#             */
/*   Updated: 2021/10/21 18:59:35 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

void	init_path_pwd(t_lexer *l, int mode)
{
	t_list	*c_envp;

	c_envp = l->envp;
	if (mode)
	{
		if (l->pathptr)
			double_free(l->pathptr);
		if (l->pwd)
			double_free(l->pwd);
	}
	while (c_envp)
		{
			if (c_envp->content && !ft_memcmp(c_envp->content, "PATH", 4))
				l->pathptr = ft_split(c_envp->content + 5, ':');
			if (c_envp->content && !ft_memcmp(c_envp->content, "PWD", 3))
				l->pwd = ft_split(c_envp->content + 4, 1);
			c_envp = c_envp->next;
		}
}
int	main(int ac, char *av[], char *envp[])
{
	void	(*sigint_c)(int);
	t_list	*c_envp;

	envp[1] = NULL;
	envp[0] = 0;
	c_envp = ft_init_env(envp, NULL);
	sigint_c = sig_handler();
	start_fonction(c_envp);
	return (0);
	sigint_c(av[ac - 1][0]);
	return (0);
}
