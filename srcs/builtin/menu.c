/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:38 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/25 19:55:06 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int is_command(char *command, char **args, t_list *l , int *last_exit)
{
	if (!(command))
		return (0);
	if (!ft_memcmp(command, "echo", 5))
		ft_echo(args, last_exit);
	else if (!ft_memcmp(command, "env", 4))
		ft_env(l);
	else if (!ft_memcmp(command, "pwd", 4))
		ft_pwd(l);
	else
		return (0);
	return (1);
}

int menu(char *command, char **args, t_lexer *l)
{
    if (!is_command(command, args, l->envp, &l->last_exit))
   		return (0);
	small_free(l, NULL, NULL, 1);
	exit(0);
}

int	check_com(char *command, char **args, t_lexer *l)
{
	if (!ft_memcmp(command, "unset", 6))
		return (0);
	else if (!ft_memcmp(command, "cd", 3))
		return (0);
	else if (!ft_memcmp(command, "export", 7))
		return (0);
	else if (ft_memcmp(command, "exit", 5))
		return (1);
	if (!args || !args[0])
		return (0);
	l->last_exit = 2;
	if (args[0] && args[1])
	{
		l->last_exit = 1;
		if (c_int(*args))
			return (print_custom("Minishell$: exit: too many arguments" , 2, 0, 1));
		l->last_exit = 2;
		return (print_custom("Minishell$: exit: numeric argument required" , 2, 0, 1));
	}
	if (c_int(*args))
	{
		l->last_exit = ft_atoi(args[0]);
		return (print_custom("" , 1, 0, 0));
	}
	return (print_custom("Minishell$: exit: numeric argument required" , 2, 0, 1));
}

int	new_menu(char *command, char **args, t_lexer *lex)
{
	t_list *l;

	if (!(command))
		return (-1);
	if (last_pipe(lex))
		return (check_com(command, args, lex));
	l = lex->envp;
	if (!ft_memcmp(command, "unset", 6))
		lex->last_exit = ft_unset(l, args);
	else if (!ft_memcmp(command, "cd", 3))
		lex->last_exit = ft_cd(args, l);
	else if (!ft_memcmp(command, "export", 7))
		lex->last_exit = ft_export(args, l);
	else if (!ft_memcmp(command, "exit", 5))
		lex->last_exit = ft_exit(lex, args);
	else
		return (-1);
	return (lex->last_exit); 
}