/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:58:22 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 18:58:23 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	print_custom(char *str, int fd, int exit_code, int saut_ligne)
{
	write(fd, str, ft_strlen(str));
	if (saut_ligne)
		write(fd, "\n", 1);
	return (exit_code);
}

char	*first_false_command(t_token *t, t_lexer *l)
{
	t_token	*tmp;

	tmp = t;
	while (t && t->type != CHAR_INUT)
	{
		tmp = t;
		t = t->n_token;
	}
	if (!t)
		return ("");
	if (!is_any_chevron(tmp) && !is_arg(t))
	{
		t = t->n_token;
		while (t)
		{
			if (!is_arg(t) && !is_any_chevron(tmp))
				t->n_token->type = CHAR_ARG;
			t = t->n_token;
		}
		return (l->buffer[get_buffer_count(l, t)]);
	}
	return (first_false_command(t->n_token, l));
}

int	ft_isal(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c <= 'Z' && c >= 'A')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
