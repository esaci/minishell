/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:35:42 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 23:37:15 by julpelle         ###   ########.fr       */
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
	l->flagr[0] = 0;
	g_exit_code = l->flagr;
}

int	wave_readline(char *ptr, t_lexer *lexer, int *last_exit)
{
	if (*g_exit_code == 130 || *g_exit_code == 131 || *g_exit_code == 2)
		lexer->last_exit = *g_exit_code;
	lexer->rl = ptr;
	if (!ptr || ptr[0] == EOF)
	{
		*last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("\nMinishell$ exit", 1, *last_exit, 1));
	}
	if (!ft_memcmp(lexer->rl, "exit", 5))
	{
		*last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("", 1, *last_exit, 0));
	}
	return (-1);
}

int	parsing_exec(char **oldptr, t_lexer *lexer, int *last_exit)
{
	char	*ptr;

	ptr = *oldptr;
	if (!parser_input(lexer))
	{
		rl_clear_history();
		small_free(lexer, ptr, NULL, 1);
		*last_exit = 1;
		return (print_custom("malloc2", 2, 1, 1));
	}
	tree_input(lexer);
	if (exec_input(lexer))
	{
		rl_clear_history();
		small_free(lexer, ptr, NULL, 1);
		*last_exit = 1;
		return (print_custom("malloc4", 2, 1, 1));
	}
	return (-1);
}

int	exit_start_function(char **oldptr, t_lexer	*lexer)
{
	char	*ptr;
	int		last_exit;

	ptr = *oldptr;
	rl_clear_history();
	if (!ptr || ptr[0] == EOF)
	{
		last_exit = lexer->last_exit;
		small_finish_free(lexer, ptr, NULL);
		return (print_custom("\nMinishell$ exit", 1, last_exit, 1));
	}
	last_exit = lexer->last_exit;
	small_finish_free(lexer, ptr, NULL);
	return (print_custom("", 1, last_exit, 0));
}

int	start_fonction(t_list *c_envp, int last_exit, char *ptr)
{
	t_lexer		*lexer;

	lexer = malloc(sizeof(t_lexer) * 2);
	if (!lexer)
		return (free_env(c_envp));
	envp_init(c_envp, lexer);
	ptr = readline("Minishell$ ");
	if (wave_readline(ptr, lexer, &last_exit) != -1)
		return (last_exit);
	while (ft_memcmp(lexer->rl, "exit", 5))
	{
		if (parsing_exec(&ptr, lexer, &last_exit) != -1)
			return (last_exit);
		add_history(ptr);
		small_free(lexer, ptr, NULL, 0);
		ptr = readline("Minishell$ ");
		if (*g_exit_code == 130 || *g_exit_code == 131 || *g_exit_code == 2)
			lexer->last_exit = *g_exit_code;
		rl_on_new_line();
		lexer->rl = ptr;
		if (!ptr || ptr[0] == EOF)
			break ;
	}
	return (exit_start_function(&ptr, lexer));
}
