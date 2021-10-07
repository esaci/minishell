/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:17:08 by esaci             #+#    #+#             */
/*   Updated: 2021/10/06 22:17:11 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	handle_old_fd(int oldfd, int fd)
{
	if (!oldfd)
		return ;
	close(fd);
	if (oldfd == 2)
		unlink("./srcs/here_doc_file");
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
	return  (count + count2);
}

int	open_infiles(t_node *n,  t_lexer *l)
{
	int	fd;
	int	count;
	int	oldfd;

	fd = 0;
	count = 0;
	oldfd = 0;
	while (n->str[count] && (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])) ||
			!ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count]))))
	{
		if (!n->str[count + 1])
			break ;
		if (!ft_memcmp(n->str[count], "<", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, fd);
			oldfd = 1;
			fd = open(n->str[count + 1], O_RDONLY);
			if (fd < 0)
				return (-count - 1);
		}
		if (!ft_memcmp(n->str[count], "<<", ft_strlen(n->str[count])))
		{
			handle_old_fd(oldfd, fd);
			oldfd = 2;
			exec_in_heredoc(n->str[count+1]);
			fd = open("./srcs/here_doc_file", O_RDWR);
		}
		count += 2;
	}
	return (fd);
	return (l->buffer[0][0]);
}

int	open_outfiles(t_node *n,  t_lexer *l)
{
	return (0);
	if (n->right)
		return (l->buffer[0][0]);
}
