/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/09/29 15:28:23 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

void	envp_init(char **envp, t_lexer *l)
{
	int	count;

	count = 0;
	while (envp[count])
	{
		if (!ft_memcmp(envp[count], "PATH", 4))
			l->pathptr = ft_split(envp[count] + 5, ':');
		if (!ft_memcmp(envp[count], "PWD", 3))
			l->pwd = ft_split(envp[count] + 4, 1);
		count++;
	}
}

int	start_fonction(char *envp[])
{
	t_lexer		*lexer;
	t_command	*cmd;
	char		*ptr;
	cmd = malloc(sizeof(t_command) * 2);
	cmd->fd_in = 0;
	cmd->fd_out = 1;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	envp_init(envp, lexer);
	readline("Minishell$ ");
	if (rl_line_buffer[0] == '\0')
		return (print_custom("Minishell$ exit", 1, 0, 1));
	while (ft_memcmp(rl_line_buffer, "exit", 4))
	{
		add_history (rl_line_buffer);
		if (!parser_input(lexer, envp))
		{
			clear_history();
			free(lexer);
			return (print_custom("malloc2", 2, 1, 1));
		}
		if (!tree_input(lexer))
		{
			rl_clear_history();
			free(lexer->pwd);
			free(lexer->pathptr);
			free(lexer);
			return (print_custom("malloc3", 2, 1, 1));
		}
/* 		exec_command(cmd, lexer->buffer); */
		/* print_tokens(lexer); */
		print_node(lexer->node);
		readline("Minishell$ ");
		if (rl_line_buffer[0] == '\0')
			break ;
		rl_on_new_line();
	}
	ptr = "";
	if (!rl_line_buffer[0])
		ptr = "Minishell$ exit\n";
	clear_history();
	free(lexer->pwd);
	free(lexer->pathptr);
	free(lexer);
	return (print_custom(ptr , 1, 0, 0));
}
