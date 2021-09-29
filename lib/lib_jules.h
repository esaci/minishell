/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_jules.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jules <Jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:25:17 by Jules             #+#    #+#             */
/*   Updated: 2021/09/29 15:01:22 by Jules            ###   ########.fr       */
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

void	ft_show_double(char **av);

#endif
