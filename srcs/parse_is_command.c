/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_is_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:01:29 by esaci             #+#    #+#             */
/*   Updated: 2021/10/01 15:01:30 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

char	*copieur(char *s)
{
	int		count;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	count = 0;
	while (s[count])
	{
		str[count] = s[count];
		count++;
	}
	str[count] = 0;
	return (str);
}

char	*parse_path2(char *arg_list, t_lexer *l)
{
	char	*ptr;
	int		tmp;

	ptr = ft_strjoin(l->pwd[0], arg_list);
	tmp = access(ptr, F_OK);
	if (tmp == 0)
	{
		if (arg_list[1] == '.')
		{
			free(ptr);
			ptr = ft_strjoin(l->pwd[0], arg_list + 2);
		}
		free(arg_list);
		return (ptr);
	}
	free(ptr);
	return (arg_list);
}

char	*parse_is_command(char *arg_list, t_lexer *l, int count)
{
	int		tmp;
	char	*ptr;

	tmp = access(arg_list, F_OK);
	if (tmp == 0)
		return (arg_list);
	tmp = 1;
	while (l->pathptr[count] && tmp != 0)
	{
		ptr = ft_strjoin(l->pathptr[count], arg_list);
		tmp = access(ptr, F_OK);
		if (tmp != 0)
			free(ptr);
		count++;
	}
	if (tmp == 0)
	{
		free(arg_list);
		return (ptr);
	}
	return (parse_path2(arg_list, l));
}
