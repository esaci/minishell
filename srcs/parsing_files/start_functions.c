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

int	custom_readline(t_lexer *lexer, char **str, int mode)
{
	char *ptr;

	ptr = *str;
	if (mode)
	{
		add_history(ptr);
		small_free(lexer, ptr, NULL, 0);
	}
	while (!ptr || !(*ptr))
	{
		if (ptr)
			free(ptr);
		ptr = readline("Minishell$ ");
		rl_on_new_line();
		lexer->rl = ptr;
		if (!ptr || ptr[0] == EOF)
		{
			small_finish_free(lexer, ptr, NULL);
			return (print_custom("\nMinishell$ exit" , 1, 1, 1));
		}
		if (!ft_memcmp(lexer->rl, "exit", 5))
		{
			small_finish_free(lexer, ptr, NULL);
			return (1);
		}
	}
	return (0);
}

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
	int			res;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (1);
	envp_init(c_envp, lexer);
	ptr = NULL;
	res = custom_readline(lexer, &ptr, 0);
	if (res)
		return (res);
	while (!res)
	{
		if (!parser_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, NULL, NULL, 1);
			return (print_custom("malloc2", 2, 1, 1));
		}
		tree_input(lexer);
		if (lexer->buffer && !ft_memcmp(lexer->buffer[0], "exit", 5))
		{
			small_free(lexer, NULL, NULL, 0);
			break;
		}
/* 		print_tokens(lexer); */
/* 		print_node(lexer->node); */
		if (exec_input(lexer))
		{
			rl_clear_history();
			small_free(lexer, NULL, NULL, 1);
			return (print_custom("malloc4", 2, 1, 1));
		}
		res = custom_readline(lexer, &ptr, 1);
	}
	rl_clear_history();
	return (0);
}
