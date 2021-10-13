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

#include "../../lib/libmin.h"

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

char	*parse_path2(char *arg_list, char *ptr2, t_lexer *l, int mode)
{
	char	*ptr;
	int		tmp;

	ptr = ft_strjoin(l->pwd[0], ptr2);
	tmp = access(ptr, F_OK);
	if (tmp == 0)
	{
		if (ptr2[1] == '.')
		{
			free(ptr);
			ptr = ft_strjoin(l->pwd[0], ptr2 + 2);
		}
		free(ptr2);
		if (mode)
			free(arg_list);
		return (ptr);
	}
	free(ptr);
	free(ptr2);
	ptr = copieur(arg_list);
	/* return (ptr); */
	if (mode)
		free(arg_list);
	return (ptr);
}

char	*parse_is_command(char *arg_list, t_lexer *l, int count, int mode)
{
	int		tmp;
	char	*ptr;
	char	*ptr2;

	ptr2 = copieur(arg_list);
	if (ptr2[0] != '/')
	{
		free(ptr2);
		ptr2 = ft_strjoin("/", arg_list);
	}
	tmp = 1;
	while (l->pathptr[count] && tmp != 0)
	{
		ptr = ft_strjoin(l->pathptr[count], ptr2);
		tmp = access(ptr, F_OK);
		if (tmp != 0)
			free(ptr);
		count++;
	}
	if (tmp == 0)
	{
		free(ptr2);
		if (mode)
			free(arg_list);
		return (ptr);
	}
	return (parse_path2(arg_list, ptr2, l, mode));
}
