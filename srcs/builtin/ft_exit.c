/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 19:24:05 by elias             #+#    #+#             */
/*   Updated: 2021/10/26 19:24:08 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	c_int(char *nbr)
{
	char	*temp;
	int		fix;

	fix = 0;
	temp = ft_itoa(ft_atoi(nbr));
	if (ft_strncmp(temp, nbr, ft_strlen(nbr)))
	{
		if (nbr[fix] == '0')
		{
			free(temp);
			return (c_int(nbr + fix + 1));
		}
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

int	ft_exit(t_lexer *l, char **args)
{
	int exit_code;

	if (!args || !args[0])
	{
		exit_code = l->last_exit;
		close_pipes(l, 1);
		small_free(l, NULL, NULL, 1);
		exit(print_custom("" , 1, exit_code, 1));
	}
	if (args[0] && args[1])
	{
		if (!c_int(*args))
			return (print_custom("Minishell$: exit: too many arguments" , 1, 1, 1));
		close_pipes(l, 1);
		small_free(l, NULL, NULL, 1);
		exit(print_custom("Minishell$: exit: numeric argument required" , 1, 2, 1));
	}
	if (c_int(*args))
	{
		exit_code = ft_atoi(args[0]);
		close_pipes(l, 1);
		small_free(l, NULL, NULL, 1);
		exit(print_custom("" , 1, exit_code, 1));
	}
	return (0);
}