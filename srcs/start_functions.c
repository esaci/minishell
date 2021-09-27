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
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	readline("Minishell: ");
	while (ft_memcmp(rl_line_buffer, "exit", 5))
	{
		if (!parser_input(lexer))
		{
			rl_clear_history();
			free(lexer);
			return (print_custom("malloc2", 2, 1, 1));
		}
		if (rl_line_buffer[0] != 0)
			add_history(rl_line_buffer);
		print_tokens(lexer);
		rl_on_new_line();
		readline("Minishell: ");
		rl_replace_line(rl_line_buffer, 0);
	}
	rl_clear_history();
	free(lexer);
	return (0);
	return(envp[0][0]);
}
