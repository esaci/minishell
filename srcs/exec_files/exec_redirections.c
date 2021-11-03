/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:17:08 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 17:20:35 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

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
		if (n->str[*count] && n->str[*count + 1])
			*fd = open(n->str[*count + 1], O_RDONLY);
		if (!n->str[*count] && *fd < 0)
			return (n->str[*count]);
		if (*fd < 0)
			return (n->str[*count + 1]);
	}
	else if (!ft_memcmp(n->str[*count], "<<", ft_strlen(n->str[*count])))
	{
		handle_old_fd(*oldfd, *fd);
		*oldfd = 2;
		*fd = *(n->fd++);
		n->archive_fd[0] = -1;
		if (!n->str[*count] && *fd < 0)
			return (n->str[*count]);
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
	while (open_infiles_suite(n, fd, &count, &oldfd) != NULL && \
	n->str[count] && (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])) \
	|| !ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count]))))
	{
		open_infiles_suite(n, fd, &count, &oldfd);
		count += 2;
	}
	return (NULL);
}

char	*open_outfiles_suite(t_node *n, int *fd
	, int count[2], int mode)
{
	if (mode == 1)
	{
		handle_old_fd(count[1], *fd);
		count[1] = 1;
		*fd = open(n->str[count[0] + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd < 0)
			return (n->str[count[0] + 1]);
	}
	if (mode == 2)
	{
		handle_old_fd(count[1], *fd);
		count[1] = 1;
		*fd = open(n->str[count[0] + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd < 0)
			return (n->str[count[0] + 1]);
	}
	return (NULL);
}

char	*open_outfiles(t_node *n, int *fd)
{
	int		c[2];
	char	*tmp;

	*fd = 1;
	c[0] = 0;
	c[1] = 0;
	n->archive_fd = n->fd;
	while (n->str[c[0]] && (!ft_memcmp(n->str[c[0]], ">", \
		ft_strlen(n->str[c[0]])) || !ft_memcmp(n->str[c[0]], \
		">>", ft_strlen(n->str[c[0]]))))
	{
		if (!n->str[c[0] + 1])
			break ;
		if (!ft_memcmp(n->str[c[0]], ">", ft_strlen(n->str[c[0]])))
			tmp = open_outfiles_suite(n, fd, c, 1);
		else if (!ft_memcmp(n->str[c[0]], ">>", ft_strlen(n->str[c[0]])))
			tmp = open_outfiles_suite(n, fd, c, 2);
		else
			break ;
		if (tmp)
			return (tmp);
		c[0] += 2;
	}
	return (NULL);
}
