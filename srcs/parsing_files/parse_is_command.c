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

char	*return_free(char *r, char *f, char *arg, int mode)
{
	if (mode)
		free(arg);
	if (f)
		free(f);
	return (r);
}

char	*parse_path2(char *arg_list, char *ptr2, t_lexer *l, int mode)
{
	char	*ptr;
	int		tmp;

	if (l->pwd && l->pwd[0])
	{
		ptr = ft_strjoin(l->pwd[0], ptr2);
		tmp = access(ptr, F_OK);
		if (tmp == 0)
		{
			if (ptr2[1] == '.' && l->pwd)
			{
				free(ptr);
				ptr = ft_strjoin(l->pwd[0], ptr2 + 2);
			}
			return (return_free(ptr, ptr2, arg_list, mode));
		}
		free(ptr);
	}
	ptr = copieur(arg_list);
	return (return_free(ptr, ptr2, arg_list, mode));
}

char	*parse_is_command(char *arg_list, t_lexer *l, int count, int mode)
{
	int		tmp;
	char	*ptr;
	char	*ptr2;

	if (!arg_list || !arg_list[0] || arg_list[0] == '.')
		return (return_free(copieur(arg_list), NULL, arg_list, mode));
	ptr2 = copieur(arg_list);
	if (ptr2 && ptr2[0] != '/')
	{
		free(ptr2);
		ptr2 = ft_strjoin("/", arg_list);
	}
	tmp = 1;
	while (l->pathptr && l->pathptr[count] && tmp != 0)
	{
		ptr = ft_strjoin(l->pathptr[count], ptr2);
		tmp = access(ptr, F_OK);
		if (tmp != 0)
			free(ptr);
		count++;
	}
	if (tmp == 0)
		return (return_free(ptr, ptr2, arg_list, mode));
	return (parse_path2(arg_list, ptr2, l, mode));
}
