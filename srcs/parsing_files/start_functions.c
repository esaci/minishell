/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/10/27 12:57:04 by julpelle         ###   ########.fr       */
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
	l->line_buffer = NULL;
}

int	start_fonction(t_list *c_envp)
{
	t_lexer		*lexer;
	char		*ptr;
	int			last_exit;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	envp_init(c_envp, lexer);
	ptr = NULL;
	get_signal();
	ptr = readline("Minishell$ ");
	lexer->rl = ptr;
	if (!ptr || ptr[0] == EOF)
	{
		last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("\nMinishell$ exit" , 1, last_exit, 1));
	}
	if (!ft_memcmp(lexer->rl, "exit", 5))
	{
		last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("" , 1, last_exit, 0));
	}
	while (ft_memcmp(lexer->rl, "exit", 5))
	{
		if (!parser_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, ptr, NULL, 1);
			print_custom("malloc2", 2, 1, 1);
			return (1);
		}
		tree_input(lexer);
/* 		print_tokens(lexer); */
		/* print_node(lexer->node); */
		if (exec_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, ptr, NULL, 1);
			return (print_custom("malloc4", 2, 1, 1));
		}
		get_signal();
		add_history(ptr);
		small_free(lexer, ptr, NULL, 0);
		ptr = readline("Minishell$ ");
		lexer->rl = ptr;
		rl_on_new_line();
		if (!ptr || ptr[0] == EOF)
			break ;
	}
	rl_clear_history();
	if (!ptr || ptr[0] == EOF)
	{
		last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("\nMinishell$ exit" , 1, last_exit, 1));
	}
	last_exit = lexer->last_exit;
	small_finish_free(lexer, ptr, NULL);
	return (print_custom("" , 1, last_exit, 0));
}
