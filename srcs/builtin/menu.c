/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:38 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/18 20:04:51 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

char    *str_low(char *str)
{
    char    *res;
    int     i;

    i = 0;
    if (!str)
        return (NULL);
    res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
    while (str[i])
    {
        if (ft_isalpha(str[i]))
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
                res[i] = str[i] + 32;
            else
                res[i] = str[i];
        }
        i++;
    }
    res[i] = '\0';
    return (res);
}

int is_command(char *command, char **args, t_list *l)
{
	if (!ft_strncmp(command, "echo", 5))
		ft_echo(args);
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
    if (!is_command(command, args, l->envp))
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
		print_env(l);
	else
		return (0);
	return (1); 
}