/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:38 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/21 19:05:43 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int is_command(char *command, char **args, t_list *l , int last_exit)
{
	if (!ft_strncmp(command, "echo", 5))
		ft_echo(args, last_exit);
	else if (!ft_strncmp(command, "env", 4))
		ft_env(l);
	else if (!ft_strncmp(command, "pwd", 4))
		ft_pwd(l);
	else
		return (0);
	return (1);
}

int menu(char *command, char **args, t_lexer *l)
{
    if (!is_command(command, args, l->envp, l->last_exit))
   		return (0);
	small_free(l, NULL, NULL, 1);
	exit(0);
}

int	new_menu(char *command, char **args, t_lexer *lex)
{
	t_list *l;

	l = lex->envp;
	if (!ft_strncmp(command, "unset", 6))
		ft_unset(l, args);
	else if (!ft_strncmp(command, "cd", 3))
		ft_cd(args, l);
	else if (!ft_strncmp(command, "export", 7))
		ft_export(args, l);
	else
		return (0);
	return (1); 
}