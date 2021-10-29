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

void	correct_path(char *ptr)
{
	int	count;

	count = 0;
	if (!ptr || !ptr[0] || ptr[0] != '"')
		return ;
	count++;
	while (ptr[count])
	{
		ptr[count - 1] = ptr[count];
		count++;
	}
	ptr[count - 1] = 0;
	ptr[count] = 0;
}

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
	correct_path(ptr);
	l->pathptr = ft_split(ptr, ':');
	free(ptr);
	ptr = custom_getenv(c_envp, "PWD");
	correct_path(ptr);
	l->pwd = ft_split(ptr, 1);
	free(ptr);
}
int	main(int ac, char *av[], char *envp[])
{
	void	(*sigint_c)(int);
	t_list	*c_envp;
	int		last_exit;

	signal_wait_input();
	c_envp = ft_init_env(envp, NULL);
	/* get_signal(); */
	last_exit = start_fonction(c_envp);
	return (last_exit);
	return (av[ac - 1][0]);
	sigint_c = sig_handler();
	sigint_c(av[ac - 1][0]);
	return (0);
}
