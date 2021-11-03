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

int	condition_infiles(t_node *n, int count)
{
	if (n->str[count] && n->str[count + 1]
		&& (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count]))
			|| !ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count]))))
		return (0);
	return (1);
}

int	condition_outfile(t_node *n, int count)
{
	if (n->str[count] && n->str[count + 1]
		&& (!ft_memcmp(n->str[count], ">", ft_strlen(n->str[count]))
			|| !ft_memcmp(n->str[count], ">>", ft_strlen(n->str[count]))))
		return (0);
	return (1);
}

char	*open_infiles(t_node *n, int *fd)
{
	int	count;
	int	oldfd;

	init_infiles(fd, &count, &oldfd, n);
	while (!condition_infiles(n, count))
	{
		if (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])))
		{
			oldfd = handle_old_fd(oldfd, *fd, 1);
			*fd = open(n->str[count + 1], O_RDONLY);
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else if (!ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count])))
		{
			oldfd = handle_old_fd(oldfd, *fd, 2);
			*fd = *(n->fd++);
			if (*fd < 0)
				return (n->str[count + 1]);
		}
		else
			break ;
		count += 2;
	}
	return (NULL);
}

char	*open_outfiles(t_node *n, int *fd)
{
	int	c;
	int	oldfd;

	init_outfile(fd, &c, &oldfd, n);
	while (!condition_outfile(n, c))
	{
		if (!ft_memcmp(n->str[c], ">", ft_strlen(n->str[c])))
		{
			oldfd = handle_old_fd(oldfd, *fd, 1);
			*fd = open(n->str[c + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (*fd < 0)
				return (n->str[c + 1]);
		}
		else if (!ft_memcmp(n->str[c], ">>", ft_strlen(n->str[c])))
		{
			oldfd = handle_old_fd(oldfd, *fd, 1);
			*fd = open(n->str[c + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (*fd < 0)
				return (n->str[c + 1]);
		}
		else
			break ;
		c += 2;
	}
	return (NULL);
}
