/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fast_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:26:50 by esaci             #+#    #+#             */
/*   Updated: 2021/10/05 17:26:52 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	id_pipe(t_lexer *l, t_node *n)
{
	t_node	*tmp;
	int		count;

	tmp = l->node;
	count = 0;
	while (tmp && tmp != n)
	{
		count++;
		tmp = tmp->right;
	}
	return (count);
}

int	ft_strlen_double(char **str)
{
	int	count;

	count = 0;
	while (str && str[count])
		count++;
	return (count);
}

t_token	*get_token_buffer(t_lexer *l, char *str)
{
	t_token	*tmp;
	int		count;

	tmp = l->tok;
	count = 0;
	while (str && l && l->buffer && l->buffer[count])
	{
		if (!ft_memcmp(l->buffer[count], str, ft_strlen(str)))
			break;
		tmp = tmp->n_token;
		count++;
	}
	return (tmp);
}

char	*merge_twoarray(char *s, char *d)
{
	int		count;
	int		count2;
	char	*ptr;

	count = ft_strlen(s) + ft_strlen(d);
	ptr = malloc(sizeof(char) * (count + 2));
	ptr[count + 1] = 0;
	count = 0;
	count2 = 0;
	while (s && s[count])
	{
		ptr[count] = s[count];
		count++;
	}
	while (d && d[count2])
	{
		ptr[count + count2] = d[count2];
		count2++;
	}
	ptr[count + count2] = 0;
	if (s)
		free(s);
	if (d)
		free(d);
/* 	s = NULL;
	d = NULL; */
	return (ptr);
}

void	fast_replacement(char **str, int count)
{
	int	count2;

	count2 = count;
	while (str[count2] && str[count2 + 1])
	{
		str[count2] = str[count2 + 1];
		count2++;
	}
}
