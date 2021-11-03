/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:17:08 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 22:13:48 by julpelle         ###   ########.fr       */
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

char	*open_infiles(t_node *n, int *fd)
{
	int	count;
	int	oldfd;

	*fd = 0;
	count = 0;
	oldfd = 0;
	n->archive_fd = n->fd;
	while (n->str[count] && (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])) ||
			!ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count]))))
	{
		if (!n->str[count + 1])
			break ;
		if (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, *fd);
			oldfd = 1;
			*fd = open(n->str[count + 1], O_RDONLY);
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else if (!ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, *fd);
			oldfd = 2;
			*fd = *(n->fd++);
			n->archive_fd[0] = -1;
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else
			break;
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
	while (n->str[count] && (!ft_memcmp(n->str[count], ">", ft_strlen(n->str[count])) ||
			!ft_memcmp(n->str[count], ">>", ft_strlen(n->str[count]))))
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
			break;
		count += 2;
	}
	return (NULL);
}
