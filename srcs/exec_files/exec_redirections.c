/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:17:08 by esaci             #+#    #+#             */
/*   Updated: 2021/11/02 04:22:24 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	check_redirection_suite(t_lexer *l, char **ptr, char *c)
{
	print_custom(c, 1, 1, 0);
	print_custom(" file can't be read/write", 1, 1, 1);
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

void	handle_old_fd(int oldfd, int fd)
{
	if (!oldfd)
		return ;
	close(fd);
}

int	count_file_redirection(t_node *left, t_node *right)
{
	int	count;
	int	count2;

	count = 0;
	while (left->str[count])
		count++;
	count2 = 0;
	while (right->str[count2])
		count2++;
	return (count + count2);
}

char	*open_infiles_suite(t_node *n, int *fd, int *count, int *oldfd)
{
	if (!ft_memcmp(n->str[*count], "<", ft_strlen(n->str[*count])))
	{
		handle_old_fd(*oldfd, *fd);
		*oldfd = 1;
		*fd = open(n->str[*count + 1], O_RDONLY);
		if (*fd < 0)
			return (n->str[*count + 1]);
	}
	else if (!ft_memcmp(n->str[*count], "<<", ft_strlen(n->str[*count])))
	{
		handle_old_fd(*oldfd, *fd);
		*oldfd = 2;
		*fd = *(n->fd++);
		n->archive_fd[0] = -1;
		if (*fd < 0)
			return (n->str[*count + 1]);
	}
	return (NULL);
}

char	*open_infiles(t_node *n, int *fd)
{
	int	count;
	int	oldfd;

	*fd = 0;
	count = 0;
	oldfd = 0;
	n->archive_fd = n->fd;
	while (open_infiles_suite(n, fd, &count, &oldfd) != NULL &&  n->str[count] && (!ft_memcmp(n->str[count], "<", \
		ft_strlen(n->str[count])) || !ft_memcmp(n->str[count], \
		"<<", ft_strlen(n->str[count]))))
	{
		open_infiles_suite(n, fd, &count, &oldfd);
		count += 2;
	}
	return (NULL);
}

char	*open_outfiles(t_node *n, int *fd)
{
	int	count;
	int	oldfd;

	*fd = 1;
	count = 0;
	oldfd = 0;
	n->archive_fd = n->fd;
	while (n->str[count] && (!ft_memcmp(n->str[count], ">", \
		ft_strlen(n->str[count])) || !ft_memcmp(n->str[count], \
		">>", ft_strlen(n->str[count]))))
	{
		if (!n->str[count + 1])
			break ;
		if (!ft_memcmp(n->str[count], ">", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, *fd);
			oldfd = 1;
			*fd = open(n->str[count + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else if (!ft_memcmp(n->str[count], ">>", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, *fd);
			oldfd = 1;
			*fd = open(n->str[count + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else
			break ;
		count += 2;
	}
	return (NULL);
}
