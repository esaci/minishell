/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:59:44 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/02 17:36:39 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	compatibility_arg(enum TOKENTYPE type, int mode)
{
	if (type == CHAR_INUT || type == CHAR_TIRET)
		return (1);
	if (type == CHAR_ARG)
		return (1);
	if ((type == CHAR_APO || type == CHAR_GUILL) && !mode)
		return (1);
	if (type == CHAR_SPACE)
		return (1);
	return (0);
	return (mode);
}

char	*remove_for_arg(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		str[count] = str[count + 1];
		count++;
	}
	if (count > 1)
		str[count - 2] = '\0';
	else
		str[count] = 0;
	return (str);
}

int	correct_name(t_lexer *l, t_token *t)
{
	char	*str;
	char	*str2;

	str = t->line;
	str2 = l->buffer[get_buffer_count(l, t)];
	if (!ft_strlen(str2))
		return (0);
	if (str[0] == '\'' || str[0] == '\"')
	{
		if (str[0] == str[ft_strlen(str2) - 1])
			return (1);
	}
	return (0);
}
