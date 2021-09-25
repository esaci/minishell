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

int	start_fonction(char *envp[])
{
	int		value;

	readline("Minishell: ");
	while (ft_memcmp(rl_line_buffer, "exit", 5))
	{
		value = parser_input(rl_line_buffer);
		if (value)
			value = pipex_custom(value, envp);
		if (value)
			print_custom("Echec du pipex", 1, 1, 1);
		if (rl_line_buffer[0] != 0)
			add_history (rl_line_buffer);
		rl_on_new_line();
		readline("Minishell: ");
		rl_replace_line(rl_line_buffer, 0);
	}
	rl_clear_history();
	return (0);
}
