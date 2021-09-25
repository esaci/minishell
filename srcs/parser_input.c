/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:30:33 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 21:30:34 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

/* int	is_e(char c, char s, char a, char b)
{
	if (c == s && c == )
} */

int	check_chevron(char *ptr)
{
	int	count;
	int	len;
	int	res;

	res = 0;
	count = 0;
	len = ft_strlen(ptr);
	while (count < len)
	{
		if (ptr[count] == '<' || ptr[count] == '>')
			res++;
		count++;
	}
	return (res);
}

int	check_pipe(char *ptr)
{
	int	count;
	int	len;
	int	res;

	res = 0;
	count = 0;
	len = ft_strlen(ptr);
	while (count < len)
	{
		if (ptr[count] == '|')
			res++;
		count++;
	}
	return (res);
}

int	parser_input(char *ptr)
{
	int	value;

	if (!ptr)
		return (0);
	value = 0;
	value += 10 * check_chevron(ptr);
	value += 100 * check_pipe(ptr);
	return (value);
}
