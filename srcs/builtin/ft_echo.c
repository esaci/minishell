/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:55:24 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 19:43:11 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

int	ft_check_echo(char *flag)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!flag)
		return (-1);
	while (flag[i++] == '-')
		count++;
	if (count != 1)
		return (-1);
	while (flag[count] == 'n')
		count++;
	if (!flag[count])
		return (1);
	return (-1);
}

int	custom_check(char *ptr, t_lexer *l)
{
	t_token	*t;

	t = get_token_buffer(l, ptr);
	if (t && t->line && t->line[0] == '\'')
		return (1);
	return (0);
}

void	ft_echo(char **args, int *lt, t_lexer *l)
{
	int	flag;
	int	last_exit;

	last_exit = *lt;
	flag = 0;
	while (ft_check_echo(args[0]) == 1)
	{
		flag = 1;
		(args)++;
	}
	while (*args)
	{
		if (!ft_strncmp(*args, "$?", 3) && !custom_check(*args, l))
			ft_putnbr_fd(last_exit, 1);
		else if (ft_strncmp(*args, "\0", 1))
			ft_putstr_fd(*args, 1);
		(args)++;
		if (*args)
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return ;
}
