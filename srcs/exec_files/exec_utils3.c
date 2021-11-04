/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:39:29 by julpelle          #+#    #+#             */
/*   Updated: 2021/11/04 00:51:14 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	check_redirection_suite(t_lexer *l, char **ptr, char *c)
{
	print_custom(c, 2, 1, 0);
	print_custom(" file can't be read/write", 2, 1, 1);
	free(ptr);
	close_pipes(l, 1);
	small_free(l, NULL, NULL, 1);
}

int	check_order_redirection(t_lexer *l, char **ptr)
{
	int		count;

	count = 0;
	while (l->buffer[count])
	{
		if (ptr[0] && !ft_memcmp(ptr[0], l->buffer[count], \
			ft_strlen(l->buffer[count]) && \
			(ft_strlen(l->buffer[count]) == ft_strlen(ptr[0]))))
		{
			check_redirection_suite(l, ptr, ptr[0]);
			return (1);
		}
		if (ptr[1] && !ft_memcmp(ptr[1], l->buffer[count], \
			ft_strlen(l->buffer[count]) && \
			(ft_strlen(l->buffer[count]) == ft_strlen(ptr[1]))))
		{
			check_redirection_suite(l, ptr, ptr[1]);
			return (1);
		}
		count++;
	}
	free(ptr);
	return (small_free(l, NULL, NULL, 0));
}

int	handle_old_fd(int oldfd, int fd, int mode)
{
	if (!oldfd)
		return (mode);
	if (fd > -1)
		close(fd);
	return (mode);
}
