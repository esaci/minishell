/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 21:35:43 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	start_fonction(void)
{
	char	*ptr;
	char	*str;
	int		value;

	ptr = 0;
	ptr = readline("Enter a line: ");
	while (ft_memcmp(ptr, "exit", 5))
	{
		value = parser_input(ptr);
		if (value)
		{
			str = ft_itoa(value);
			print_custom(str, 1, 0, 1);
			free(str);
		}
		if (ptr[0] != 0)
			add_history (ptr);
		if (ptr)
			free(ptr);
		rl_on_new_line();
		ptr = readline("Enter a line: ");
	}
	rl_clear_history();
	return (0);
}
