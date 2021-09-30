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

typedef	enum	TOKENTYPE
{
	CHAR_TMP = -1,
	CHAR_INUT = 1,
	CHAR_PIPE = '|',
	CHAR_GUILL = '\"',
	CHAR_APO = '\'',
	CHAR_DCHEVG = 59,
	CHAR_CHEVG = '<',
	CHAR_DCHEVD = 61,
	CHAR_CHEVD = '>',
	CHAR_DOLL = '$',
	CHAR_INTER = '?',
	CHAR_PARO = '(',
	CHAR_PARF = ')',
	CHAR_POINT = '.',
	CHAR_SPACE = ' ',
	CHAR_TIRET = '-',
	CHAR_ET = '&',
	CHAR_Z = 0,
	CHAR_TAB = '\t',
	CHAR_NL = '\n',
	CHAR_ERROR = '!',
}	TOKENTYPE;

typedef	enum	NODETYPE
{
	NODE_ERROR = 0,
	NODE_PIPE = 1,
	NODE_FILEIN = 2,
	NODE_FILEOUT = 3,
	NODE_PATHCOM = 4,
	NODE_ARG = 5,
}	NODETYPE;

typedef struct s_pip
{
	int		fd[2];
	int		tmp[2];
	char	**pathptr;
	char	**pwd;
	char	*tmptr;
	char	**b_ptr;
	int		errnum;
	int		b_ac;
	int		*b_pid;
	int		*b_pfd1;
}	t_pip;

typedef	struct s_token
{
	TOKENTYPE	type;
	char				*line;
	struct s_token		*n_token;
}	t_token;

typedef	struct s_lexer
{
	t_token		*tok;
	int			len;
	char		**buffer;
}	t_lexer;

typedef	struct s_node
{
	NODETYPE		type;
	char			*str;
	struct s_node	*before;
	struct s_node	*after;
}	t_node;

int					start_fonction(char *envp[]);
void				*sig_handler();
t_lexer				*parser_input(t_lexer *lexer);
t_token				*parser_next_token(t_token *tok);
int					parser_output(t_lexer *lexer);
int					fill_buffer(t_lexer *lexer);
int					pipex_custom(int value, char *envp[]);
int					print_custom(char *str, int fd, int exit_code, int saut_ligne);
int					print_tokens(t_lexer *l);
int					free_lexer_tokens(t_lexer *lexer);
int					init_lexer(t_lexer *lexer);
int					lexer_start(t_lexer *lexer);
t_node				*tree_input(t_lexer *lexer, t_node **node);
#endif
