/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:35:04 by esaci             #+#    #+#             */
/*   Updated: 2021/09/24 15:43:16 by esaci            ###   ########.fr       */
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

int				start_fonction(char *envp[]);
void			sig_handler();
int				parser_input(char *ptr);
int				pipex_custom(int value, char *envp[]);
int				print_custom(char *str, int fd, int exit_code, int saut_ligne);

#endif
