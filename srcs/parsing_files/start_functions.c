/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/10/22 23:50:02 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	envp_init(t_list *c_envp, t_lexer *l)
{
	l->last_exit = 0;
	l->tok = NULL;
	l->buffer = NULL;
	l->node = NULL;
	l->envp = c_envp;
	l->pathptr = NULL;
	l->pwd = NULL;
}

int	start_fonction(t_list *c_envp)
{
	t_lexer		*lexer;
	char		*ptr;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	envp_init(c_envp, lexer);
	ptr = NULL;
	ptr = readline("Minishell$ ");
	if (!ptr || ptr[0] == EOF || !ft_memcmp(rl_line_buffer, "exit", 5))
	{
		small_free(lexer, ptr, NULL, 1);
		if (ft_memcmp(rl_line_buffer, "exit", 5))
			return (print_custom("\nMinishell$ exit" , 1, 0, 1));
		return (print_custom("", 1, 0, 0));
	}
	while (ft_memcmp(rl_line_buffer, "exit", 5))
	{
		if (!parser_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, NULL, NULL, 1);
			return (print_custom("malloc2", 2, 1, 1));
		}
		tree_input(lexer);
/* 		print_node(lexer->node); */
		if (exec_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, NULL, NULL, 1);
			return (print_custom("malloc4", 2, 1, 1));
		}
		rl_line_buffer[1] = '\0';
		add_history(ptr);
		small_free(lexer, ptr, NULL, 0);
		ptr = readline("Minishell$ ");
		rl_on_new_line();
		if (!ptr || ptr[0] == EOF)
			break ;
	}
	rl_clear_history();
	/* small_free(lexer, ptr, NULL, 1); */
	small_finish_free(lexer, ptr, NULL);
	if (ft_memcmp(rl_line_buffer, "exit", 5))
		return (print_custom("\nMinishell$ exit" , 1, 0, 1));
	return (print_custom("" , 1, 0, 0));
}
