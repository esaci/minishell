/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:34:34 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 03:32:26 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

char	*correct_path(char *ptr)
{
	int	count;

	count = 0;
	if (!ptr || !ptr[0] || ptr[0] != '"')
		return (ptr);
	count++;
	while (ptr[count])
	{
		ptr[count - 1] = ptr[count];
		count++;
	}
	if (count > 1)
		ptr[count - 2] = 0;
	ptr[count - 1] = 0;
	return (ptr);
}

void	gest_malloc(char **str, char *ptr, t_lexer *l)
{
	if (str || ptr)
		return ;
	exit(small_free(l, NULL, NULL, 1));
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
	ptr = custom_getenv(c_envp, "PATH", 0);
	gest_malloc(NULL, ptr, l);
	l->pathptr = ft_split(ptr, ':');
	free(ptr);
	gest_malloc(l->pathptr, NULL, l);
	ptr = custom_getenv(c_envp, "PWD", 0);
	gest_malloc(NULL, ptr, l);
	l->pwd = ft_split(ptr, 1);
	free(ptr);
	gest_malloc(l->pwd, NULL, l);
}

int	main(int ac, char *av[], char *envp[])
{
	t_list	*c_envp;
	int		last_exit;

	(void)ac;
	(void)av;
	signal_wait_input();
	c_envp = ft_init_env(envp, NULL);
	last_exit = start_fonction(c_envp, 0, NULL);
	return (last_exit);
}
