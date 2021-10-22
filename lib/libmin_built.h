/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin_built.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:25:17 by Jules             #+#    #+#             */
/*   Updated: 2021/10/22 23:53:26 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_BUILT_H
# define LIBMIN_BUILT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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
# include "../fcts/libft/libft.h"
# include "../fcts/GNL/get_next_line.h"
# include "libmin.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

typedef struct  s_list
{
	char	*content;
	void	*next;
}	            t_list;

typedef struct 	s_lexer t_lexer;

// Builtin

int		menu(char *command, char **args, t_lexer *l);
int		new_menu(char *command, char **args, t_lexer *l);
void	ft_pwd(t_list *l);
void	ft_env(t_list *env);
void	ft_echo(char **args, int last_exit);
int 	ft_check_echo(char *flag);
void    ft_cd(char **args, t_list *l);
void    ft_unset(t_list *l, char **args);
void	ft_export(char **args, t_list *e);

//Environnement

t_list	*ft_envp(char *envp[], char *content, t_list *v_env);
void	ft_lst_pushback(t_list **lst, char *content);
t_list	*ft_init_env(char *envp[], t_list *env);
t_list	*ft_add_env(char *to_add, t_list *env);
t_list	*ft_tab_to_lst(char *table[]);
t_list	*ft_del_variable(char *variable, t_list *env);
t_list	*free_env(t_list *env);
int		utils_strlen_env(t_list *l);
char	**generate_custom_envp(t_list *v_env);
t_list	*create_envp(t_list	*env);
char	*custom_getenv(t_list *l, char *ptr);
int		print_env(t_list *env);

#endif
