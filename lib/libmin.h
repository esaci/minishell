/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:35:04 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 17:33:30 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_H
# define LIBMIN_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../fcts/libft/libft.h"
# include "../fcts/GNL/get_next_line.h"
# include <sys/stat.h>
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
# include <errno.h>
# include <sys/errno.h>
# include "libmin_built.h"
# include "libmin_sign.h"

typedef enum TOKENTYPE
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
	CHAR_SPACE = ' ',
	CHAR_TIRET = '-',
	CHAR_Z = 0,
	CHAR_TAB = '\t',
	CHAR_NL = '\n',
	CHAR_ERROR = '!',
	CHAR_ARG = 'E',
}	t_TOKENTYPE;

typedef enum NODETYPE
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
}	t_NODETYPE;

int						*g_exit_code;

typedef struct s_list	t_list;

typedef struct s_pip
{
	int		tmp[2];
	char	*tmptr;
	int		errnum;
	int		*pid;
	int		*pfd;
	int		*ppd;
}	t_pip;

typedef struct s_token
{
	t_TOKENTYPE			type;
	char				*line;
	struct s_token		*n_token;
}	t_token;

typedef struct s_node
{
	t_NODETYPE		type;
	char			**str;
	struct s_node	*right;
	struct s_node	*left;
	int				*fd;
	int				*archive_fd;
}	t_node;

typedef struct s_lexer
{
	t_token		*tok;
	t_token		*c_tok;
	t_node		*node;
	t_pip		*pip;
	t_list		*envp;
	char		**buffer;
	char		**pathptr;
	char		**pwd;
	char		*line_buffer;
	char		*rl;
	int			len;
	int			flagr[1];
	int			last_exit;
}	t_lexer;

void				init_line_buffer(t_lexer *l, int count2, int count3, \
					int count4);
int					len_needed(t_lexer *l);
int					malloc_free_buff(t_lexer *l);
void				ignore_all_buff(t_lexer *l, int	*c2, int *c4);
int					flag_arg(int count, int count2, t_lexer *l);
void				init_path_pwd(t_lexer *l, int mode);
int					start_fonction(t_list *c_envp, int last_exit, char *ptr);
void				*sig_handler(void);
t_lexer				*parser_input(t_lexer *lexer);
t_token				*parser_chevron(t_token *t, enum TOKENTYPE type);
t_token				*parser_in_between(t_token *t, enum TOKENTYPE type);
t_token				*parser_until_not(t_token *t, enum TOKENTYPE type, \
					enum TOKENTYPE type2);
t_token				*parser_until_space(t_token *tok);
t_token				*parser_next_token(t_token *tok);
t_token				*check_apo(t_token *t, int mode);
int					parser_output(t_lexer *lexer);
int					fill_buffer(t_lexer *lexer);
int					copy_buffer(char **buffu, t_token *tok, int fd[2]);
int					print_custom(char *str, int fd, int exit_code,
						int saut_ligne);
int					print_tokens(t_lexer *l);
int					print_node(t_node *node);
void				full_print(char **str);
int					print_str_node(t_node *n, char *str, int count2);
int					free_lexer_tokens(t_lexer *lexer, int mode);
int					init_lexer(t_lexer *lexer);
int					lexer_start(t_lexer *lexer, int mode);
t_node				*tree_input(t_lexer *lexer);
char				*parse_is_command(char *arg_list, t_lexer *l,
						int count, int mode);
t_NODETYPE			is_any_chevron(t_token *t);
t_NODETYPE			is_any_command(t_lexer *l, t_token *t, t_token *oldt);
int					is_redirection(t_node *n2);
int					search_pipe(t_node *n, t_token *t, t_lexer *l);
int					search_command(t_node *n, t_token *t, t_lexer *l);
int					search_node_str_com(t_node *n, t_token *t, t_lexer *l);
int					*join_int(int *fd, char *str, t_lexer *l);
int					add_path(char **ptr, t_token *t, t_lexer *l, char *err);
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
t_node				*exec_pipe(t_lexer *l, t_node *n, int count, int *fdin);
int					exec_com(t_lexer *l, t_node *n, int count);
int					init_pip(t_lexer *l);
void				close_pipes(t_lexer *l, int mode);
int					free_pip(t_lexer *l, int exit);
int					id_pipe(t_lexer *l, t_node *n);
int					ft_strlen_double(char **str);
char				*merge_twoarray(char *s, char *d, int mode);
t_token				*get_token_buffer(t_lexer *l, char *str);
int					full_close(t_lexer *l);
int					full_free(t_lexer *l);
int					count_right_nodes(t_lexer *l);
int					waiter_input(t_lexer *l, int count);
int					count_file_redirection(t_node *left, t_node *right);
char				*open_infiles(t_node *n, int *fd);
char				*open_outfiles(t_node *n, int *fd);
int					check_order_redirection(t_lexer *l, char **ptr);
int					exec_in_heredoc(char *limiter, int *fd, t_lexer *l);
int					last_pipe(t_lexer *l);
char				*remove_for_arg(char *str);
void				check_for_arg(char **str, t_lexer *l, t_node *n);
int					compatibility_arg(enum TOKENTYPE type, int mode);
int					correct_name(t_lexer *l, t_token *t);
int					double_free(char **str);
int					free_lexer_nodes(t_lexer *l, int mode);
t_token				*unlink_free_return(t_token *t, int skip);
int					small_free(t_lexer *l, void *ptr, void *ptr2, int mode);
int					small_finish_free(t_lexer *l, void *ptr, void *ptr2);
int					arg_gestion(char *buff, t_token *t);
char				*copieur(char *s);
void				init_both_nodes(t_node *left, t_node *right);
void				close_archive(int *ptr);
int					len_needed(t_lexer *l);
char				*get_name(char *arg);
void				ultime_close_archive(t_lexer *l);
int					ft_isal(int c);
int					is_apo(char *ptr, char c);
int					malloc_node_redir(t_node *n, t_token *t, \
					enum TOKENTYPE r1, enum TOKENTYPE r2);
int					free_pip_2(t_lexer *l);
char				*merge_suite(int mode, char *ptr, char *s, char *d);
void				copy_arg(char *str, char *ptr, int *count2);
int					len_var(t_lexer *l, char *ptr);
int					countain_doll(char *ptr);
int					last_pipe(t_lexer *l);
void				utils2_com_nopipe(t_lexer *l, t_node *n, int count);
void				error_pipe(t_lexer *l, int count);
void				execve_check_error(t_lexer *l, t_node *n, char **p, int t);
void				check_redirection_suite(t_lexer *l, char **ptr, char *c);
int					check_order_redirection(t_lexer *l, char **ptr);
int					handle_old_fd(int oldfd, int fd, int mode);
int					search_chevg(t_node *n, t_token *t, t_lexer *l, int *count);
int					search_chevd(t_node *n, t_token *t, t_lexer *l, int *count);
void				free_loop_fd_in(t_node *n);
void				free_loop_fd_out(t_node *n);
void				infile_exit_code(void);
void				init_infiles(int *fd, int *count, int *oldfd, t_node *n);
void				init_outfile(int *fd, int *count, int *oldfd, t_node *n);
#endif
