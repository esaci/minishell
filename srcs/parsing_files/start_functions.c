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
	char		*ptr;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	envp_init(envp, lexer);
	ptr = NULL;
	ptr = readline("Minishell$ ");
	if (!ptr || ptr[0] == EOF)
	{
		double_free(lexer->pwd);
		double_free(lexer->pathptr);
		free(lexer);
		free(ptr);
		return (print_custom("\nMinishell$ exit1", 1, 0, 1));
	}
	while (ft_memcmp(rl_line_buffer, "exit", 5))
	{
		add_history(rl_line_buffer);
		if (!parser_input(lexer, envp))
		{
			double_free(lexer->pwd);
			double_free(lexer->pathptr);
			rl_clear_history();
			free(lexer);
			return (print_custom("malloc2", 2, 1, 1));
		}
/* 		print_tokens(lexer); */
		tree_input(lexer);
		if (exec_input(lexer))
		{
			rl_clear_history();
			double_free(lexer->pwd);
			double_free(lexer->pathptr);
			free(lexer);
			return (print_custom("malloc4", 2, 1, 1));
		}
		/* print_node(lexer->node); */
/* 		print_env(lexer); */
		rl_line_buffer[1] = '\0';
		free(ptr);
		free_lexer_nodes(lexer);
		free_lexer_tokens(lexer);
		ptr = readline("Minishell$ ");
		rl_on_new_line();
		if (!ptr || ptr[0] == EOF)
			break ;
	}
	clear_history();
	double_free(lexer->pwd);
	double_free(lexer->pathptr);
	free(lexer);
	if (ft_memcmp(rl_line_buffer, "exit", 5))
		free(ptr);
	return (print_custom("\nMinishell$ exit\n" , 1, 0, 0));
}
