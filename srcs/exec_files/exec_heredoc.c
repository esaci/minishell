/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:17:53 by esaci             #+#    #+#             */
/*   Updated: 2021/11/03 22:25:00 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

char	*apply_doll_suite(char *ptr, t_lexer *l, int *count2, char *str)
{
	char	*var;
	int		count;

	count = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
		{
			var = get_name(ptr + count + 1);
			copy_arg(str, custom_getenv(l->envp, var, 0), count2);
			free(var);
			count++;
			while (ptr && ptr[count] && ft_isal(ptr[count]))
				count++;
		}
		else
			str[*count2++] = ptr[count++];
	}
	return (str);
}

char	*apply_doll(char *ptr, t_lexer *l)
{
	int		count;
	int		count2;
	char	*str;

	count = ft_strlen(ptr);
	count += len_var(l, ptr);
	str = malloc(sizeof(char) * (count + 2));
	if (!str)
		return (NULL);
	str[count] = 0;
	str[count + 1] = 0;
	count = 0;
	count2 = 0;
	str = apply_doll_suite(ptr, l, &count2, str);
	str[count2] = 0;
	free(ptr);
	return (str);
}

int	exec_in_heredoc(char *limiter, int *fdu, t_lexer *l)
{
	char	*ptr;
	int		fd;

	*fdu = open("./srcs/here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0777);
	fd = open("./srcs/here_doc_file", O_RDWR);
	if (fd < 0)
		exit(print_custom("here_doc file can't be read/write", 2, 1, 1));
	print_custom(">", 2, 1, 0);
	while (get_next_line(0, &ptr) > 0)
	{
		if (!ft_memcmp(ptr, limiter, ft_strlen(ptr))
			&& ft_strlen(limiter) == ft_strlen(ptr))
			break ;
		print_custom(">", 2, 1, 0);
		if (countain_doll(ptr))
			ptr = apply_doll(ptr, l);
		print_custom(ptr, fd, 1, 1);
		free(ptr);
	}
	if (ptr)
		free(ptr);
	if (fd > -1)
		close(fd);
	unlink("./srcs/here_doc_file");
	return (0);
}

void	close_archive(int *ptr)
{
	int	count;

	count = 0;
	while (ptr && ptr[count] > -1)
		close(ptr[count++]);
}
