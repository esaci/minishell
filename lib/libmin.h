/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:35:04 by esaci             #+#    #+#             */
/*   Updated: 2021/09/29 12:08:08 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_H
# define LIBMIN_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../fcts/libft/libft.h"
# include "../fcts/GNL/get_next_line.h"
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

// Lib Jules
# include "lib_jules.h"
# include "libmin_exec.h"

typedef	enum	TOKENTYPE
{
	CHAR_TMP = -1,
	CHAR_INUT = 'I',
	CHAR_PIPE = '|',
	CHAR_GUILL = '\"',
	CHAR_APO = '\'',
	CHAR_DCHEVG = 59,
	CHAR_CHEVG = '<',
	CHAR_DCHEVD = 61,
	CHAR_CHEVD = '>',
	CHAR_DOLL = '$',
	CHAR_INTER = '?',
	CHAR_SPACE = ' ',
	CHAR_TIRET = '-',
	CHAR_ET = '&',
	CHAR_Z = 0,
	CHAR_TAB = '\t',
	CHAR_NL = '\n',
	CHAR_ERROR = '!',
	CHAR_ARG = 'E',
}	TOKENTYPE;

typedef	enum	NODETYPE
{
	NODE_ERROR = 0,
	NODE_PIPE = '|',
	NODE_FILEIN = '<',
	NODE_DFILEIN = '=',
	NODE_FILEOUT = '>',
	NODE_DFILEOUT = '?',
	NODE_PATHCOM = 'C',
	NODE_NOCOM = 'N',
	NODE_ARG = 'A',
}	NODETYPE;

typedef struct s_pip
{
	int		tmp[2];
	char	*tmptr;
	int		errnum;
	int		*pid;
	int		*pfd;
	int		*ppd;
}	t_pip;

typedef	struct s_token
{
	TOKENTYPE	type;
	char				*line;
	struct s_token		*n_token;
}	t_token;

typedef	struct s_node
{
	NODETYPE		type;
	char			**str;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

typedef	struct s_lexer
{
	t_token		*tok;
	t_node		*node;
	int			len;
	char		**buffer;
	t_pip		*pip;
	char		**envp;
	char		**pathptr;
	char		**pwd;
}	t_lexer;

int					start_fonction(char *envp[]);
void				*sig_handler();
t_lexer				*parser_input(t_lexer *lexer, char **envp);
t_token				*parser_next_token(t_token *tok);
int					parser_output(t_lexer *lexer);
int					fill_buffer(t_lexer *lexer);
int					pipex_custom(int value, char *envp[]);
int					print_custom(char *str, int fd, int exit_code, int saut_ligne);
int					print_tokens(t_lexer *l);
int					print_node(t_node *node);
int					print_str_node(t_node *n, char *str, int count2);
int					free_lexer_tokens(t_lexer *lexer);
int					init_lexer(t_lexer *lexer, char **envp);
int					lexer_start(t_lexer *lexer);
t_node				*tree_input(t_lexer *lexer);
char				*parse_is_command(char *arg_list, t_lexer *l, int count);
NODETYPE			is_any_chevron(t_token *t);
NODETYPE			is_any_command(t_lexer *l, t_token *t, t_token *oldt);
int					is_redirection(t_node *n2);
int					search_pipe(t_node *n, t_token *t, t_lexer *l);
int					search_command(t_node *n, t_token *t, t_lexer *l);
void				add_path(char **ptr, t_token *t, t_lexer *l);
int					tree_define_left(t_node *n, t_token *t, t_lexer *l);
int					tree_define_right(t_node *n, t_token *t, t_lexer *l);
int					tree_define_command(t_node *n, t_token *t, t_lexer *l);
int					search_infile(t_node *n, t_token *t, t_lexer *l);
int					search_outfile(t_node *n, t_token *t, t_lexer *l);
int					get_buffer_count(t_lexer *l, t_token *t);
char				*first_false_command(t_token *t, t_lexer *l);
int					nbr_com(t_lexer *l, t_token *t);
void				no_com_fill(t_node *n, t_lexer *l, t_token *t);
int					is_arg(t_token *t);
int					exec_input(t_lexer *l);
t_node				*exec_pipe(t_lexer *l, t_node *n);
int					exec_com(t_lexer *l, t_node *n);
int					init_pip(t_lexer *l);
int					free_pip(t_lexer *l, int exit);
#endif

