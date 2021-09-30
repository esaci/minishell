/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_jules.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:25:17 by Jules             #+#    #+#             */
/*   Updated: 2021/09/30 14:43:05 by Jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_JULES_H
# define LIB_JULES_H

#include "libmin.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

# define SUCCESS 0
# define ERROR 1
# define ERROR_INPUT 2

// Jules

typedef struct	s_list	t_list;

typedef struct	s_list
{
	char	*content;
	t_list	*next;

}	t_list;

typedef struct	s_command
{
	char	*name;
	int		operation;
	int		fd_in;
	int		fd_out;
	int		flag;
	char	**args;
	char	**args_cpy;
}	t_command;

typedef struct s_builtin
{
	char	*str;
	//void	(*f)(t_command *)
}	t_builtin;


void	exec_command(t_command *cmd, char **buffer);
int		check_arg(char	*str);
int		ft_echo_check(t_command *cmd);
void	ft_echo(t_command *cmd);

void	ft_pwd(t_command *cmd);

void	ft_cd(t_command *cmd);

t_list	*convert_tab_list(char *table[]);
t_list	**ft_envp(char *envp[], char *content, t_list *env);
void	ft_env(t_command *cmd);


t_list	**ft_init_env(char *envp[]);
void	fill_env(char *envp[]);
void	ft_show_double(char **av);

// LST BONUS
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lst_pushback(t_list **list, char *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	recursive_clear(t_list *ptr, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lst_show(t_list *list);

#endif
