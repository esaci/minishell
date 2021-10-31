/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 18:38:08 by elias             #+#    #+#             */
/*   Updated: 2021/10/23 18:38:10 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	is_apo(char *ptr, char c)
{
	int	count;

	count = 0;
	while (ptr[count])
	{
		if (ptr[count] == c)
			return (1);
		count++;
	}
	return (0);
}

char	*get_name(char *arg)
{
	int		count;
	char	*ptr;
	int		count2;

	count = 0;
	while (arg && arg[count] && (ft_isal(arg[count])
			|| (count && ft_isalnum(arg[count]))))
		count++;
	ptr = malloc(sizeof(char) * (count + 10));
	if (!ptr)
		return (NULL);
	ptr[count] = 0;
	count2 = 0;
	while (count2 < count)
	{
		ptr[count2] = arg[count2];
		count2++;
	}
	return (ptr);
}

void	add_arg(t_lexer *l, int *count4, int *count2, int count3)
{
	char	*ptr;
	char	*var;
	int		count;

	var = get_name(l->rl + *count2 + 1);
	ptr = custom_getenv(l->envp, var, 0);
	count = 0;
	while (ptr && ptr[count])
		l->line_buffer[(*count4)++] = ptr[count++];
	(*count2)++;
	if (!ft_isalnum(l->rl[*count2]) && l->rl[*count2] != '_'
		&& ((l->rl[*count2] != '\'' && l->rl[*count2] != '\"') || count3))
		l->line_buffer[(*count4)++] = '$';
	count = 0;
	while (l->rl && l->rl[*count2]
		&& (ft_isalnum(l->rl[*count2]) || l->rl[*count2] == '_'))
	{
		(*count2)++;
		if (!ft_isal(l->rl[*count2 - 1]) && !count)
			break ;
		count++;
	}
	free(var);
	free(ptr);
}

int	len_needed(t_lexer *l)
{
	int		count;
	int		count2;
	char	*ptr;
	char	*var;

	count = ft_strlen(l->rl);
	count2 = 0;
	while (l->rl[count2])
	{
		if (l->rl[count2] == '$'
			&& l->rl[count2 + 1] && l->rl[count2 + 1] != '?')
		{
			var = get_name(l->rl + count2 + 1);
			ptr = custom_getenv(l->envp, var, 0);
			count += ft_strlen(ptr);
			free(var);
			free(ptr);
		}
		count2++;
	}
	return (count);
}

void	init_line_buffer(t_lexer *l, int c2, int c3, int c4)
{
	int	c1;

	if (malloc_free_buff(l))
		return ;
	c1 = 0;
	while (l->rl[c2])
	{
		c1 = flag_arg(c1, c2, l);
		if (l->rl[c2] == '\"' && (is_apo(l->rl + c2 + 1, '\"') || c3))
		{
			c3 = 1 - c3;
			l->line_buffer[c4++] = l->rl[c2++];
		}
		else if (!c3 && l->rl[c2] == '\'' && is_apo(l->rl + c2 + 1, '\''))
			ignore_all_buff(l, &c2, &c4);
		else if (l->rl[c2] == '$'
			&& l->rl[c2 + 1] && l->rl[c2 + 1] != '?' && !c1)
			add_arg(l, &c4, &c2, c3);
		else
			l->line_buffer[c4++] = l->rl[c2++];
	}
	l->line_buffer[c4] = 0;
}
