/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_jules.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:25:17 by Jules             #+#    #+#             */
/*   Updated: 2021/10/04 12:57:50 by julespellet      ###   ########.fr       */
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


int		exec_command(char **buffer);
int		ft_echo_check(t_command *cmd);
void	ft_echo(t_command *cmd);

void	ft_pwd(t_command *cmd);

void	ft_cd(t_command *cmd);

t_list	*convert_tab_list(char *table[]);
t_list	**ft_envp(char *envp[], char *content, t_list *env);
void	ft_env(t_command *cmd);


//void	fill_env(char *envp[]);
//void	ft_show_double(char **av);

//ENVIRONMENT
t_list	**ft_envp(char *envp[], char *content, t_list *env);
char	*ft_getenv(char *key);
void	ft_init_env(char *envp[]);
void	ft_add_env(char *to_add);
t_list	**ft_getaddenv(void);
t_list	*ft_getallenv(void);
t_list	*ft_new_list_elem(char *content);


// LST BONUS
t_list  *ft_new_elem(char *content);
void	ft_lst_pushback(t_list **lst, char *content);
t_list	*ft_tab_to_lst(char **table);


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
