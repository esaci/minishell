/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/09/30 14:43:38 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	start_fonction(char *envp[])
{
	t_lexer		*lexer;
	t_command	*cmd;
	t_list		*env;

	lexer = malloc(sizeof(t_lexer) * 2);
	cmd = malloc(sizeof(t_command) * 2);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!lexer)
		return (1);
	readline("Minishell> ");
	while (ft_memcmp(rl_line_buffer, "exit", 4))
	{
		if (!parser_input(lexer))
		{
			clear_history();
			free(lexer);
			return (print_custom("malloc2", 2, 1, 1));
		}
		env = *ft_init_env(envp);
		//fill_env(envp);
		exec_command(cmd, lexer->buffer);
		if (rl_line_buffer[0] != 0)
			add_history(rl_line_buffer);
		readline("Minishell> ");
		rl_on_new_line();
		//rl_replace_line(rl_line_buffer, 0);
	}
	clear_history();
	free(lexer);
	return (0);
	return(envp[0][0]);
}
