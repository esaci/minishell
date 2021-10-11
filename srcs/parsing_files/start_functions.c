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

#include "../../lib/libmin.h"

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
	ptr = readline("Minishell$ ");
	if (!ptr || ptr[0] == EOF)
	{
		free(ptr);
		return (print_custom("\nMinishell$ exit", 1, 0, 1));
	}
	while (ft_memcmp(rl_line_buffer, "exit", 5))
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
		print_tokens(lexer);
		print_node(lexer->node);
		print_env(lexer);
/* 		if (exec_input(lexer))
		{
			rl_clear_history();
			free(lexer->pwd);
			free(lexer->pathptr);
			free(lexer);
			return (print_custom("malloc4", 2, 1, 1));
		} */
		ptr = readline("Minishell$ ");
		rl_on_new_line();
		if (!ptr || ptr[0] == EOF)
			break ;
		free(ptr);
	}
	if (ptr[0] == EOF)
	{
		free(ptr);
		ptr = "\nMinishell$ exit\n";
	}
	else
	{
		free(ptr);
		ptr = "";
	}
	clear_history();
	free(lexer->pwd);
	free(lexer->pathptr);
	free(lexer);
	return (print_custom(ptr , 1, 0, 0));
}
