/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:17:53 by esaci             #+#    #+#             */
/*   Updated: 2021/10/06 23:18:35 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

int	exec_in_heredoc(char *limiter)
{
	char	*ptr;
	int		fd;

	fd = open("./srcs/here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit(print_custom("here_doc file can't be read/write", 2, 1, 1));
	while (get_next_line(0, &ptr) > 0)
	{
		rl_line_buffer[0] = '>';
		rl_line_buffer[1] = 0;
		if (!ft_memcmp(ptr, limiter, ft_strlen(ptr))
			&& ft_strlen(limiter) == ft_strlen(ptr))
			break ;
		write(fd, ptr, ft_strlen(ptr));
		write(fd, "\n", 1);
		free(ptr);
	}
	if (ptr)
		free(ptr);
	close(fd);
	return (0);
}
