/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:06:08 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 18:00:26 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	free_pip_2(t_lexer *l)
{
	if (!l->pip->ppd)
	{
		free(l->pip->pid);
		return (1);
	}
	return (0);
}

char	*merge_suite(int mode, char *ptr, char *s, char *d)
{
	if (mode == 3)
		return (ptr);
	if (mode == 2)
	{
		free(d);
		return (ptr);
	}
	if (s)
		free(s);
	if (!mode)
		return (ptr);
	if (d)
		free(d);
	return (ptr);
}

int	countain_doll(char *ptr)
{
	int	count;

	count = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
			return (1);
		count++;
	}
	return (0);
}

int	len_var(t_lexer *l, char *ptr)
{
	int		count;
	int		count2;
	char	*str;
	char	*var;

	count = 0;
	count2 = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
		{
			var = get_name(ptr + count + 1);
			str = custom_getenv(l->envp, var, 0);
			count2 += ft_strlen(str);
			free(var);
			free(str);
		}
		count++;
	}
	return (count2);
}

void	copy_arg(char *str, char *ptr, int *count2)
{
	int	count3;

	count3 = 0;
	while (ptr && ptr[count3])
		str[(*count2)++] = ptr[count3++];
	free(ptr);
}
