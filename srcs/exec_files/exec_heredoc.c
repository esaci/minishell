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

int	countain_doll(char *ptr)
{
	int	count;

	count = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
			return (1);
		count++;
	}
	return (0);
}

int		len_var(t_lexer *l, char *ptr)
{
	int		count;
	int		count2;
	char	*str;
	char	*var;

	count = 0;
	count2 = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
		{
			var = get_name(ptr + count + 1);
			str = custom_getenv(l->envp, var);
			count2 += ft_strlen(str);
			free(var);
			free(str);
		}
		count++;
	}
	return (count2);
}

void	copy_arg(char *str, char *ptr, int *count2)
{
	int	count3;

	count3 = 0;
	while (ptr && ptr[count3])
		str[(*count2)++] = ptr[count3++];
	free(ptr);
}

char	*apply_doll(char *ptr, t_lexer *l)
{
	int		count;
	int		count2;
	char	*str;
	char	*var;

	count = ft_strlen(ptr);
	count += len_var(l, ptr);
	str = malloc(sizeof(char) * (count + 2));
	if (!str)
		return (NULL);
	str[count] = 0;
	str[count + 1] = 0;
	count = 0;
	count2 = 0;
	while (ptr && ptr[count])
	{
		if (ptr[count] == '$')
		{
			var = get_name(ptr + count + 1);
			copy_arg(str, custom_getenv(l->envp, var), &count2);
			free(var);
			count++;
			while (ptr && ptr[count] && ft_isalnum(ptr[count]))
				count++;
		}
		else
			str[count2++] = ptr[count++];
	}
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
		write(fd, ptr, ft_strlen(ptr));
		write(fd, "\n", 1);
		free(ptr);
	}
	if (ptr)
		free(ptr);
	close(fd);
	unlink("./srcs/here_doc_file");
	return (0);
}

void	close_archive(int *ptr)
{
	int	count;

	count = 0;
	while (ptr && ptr[count] != -1)
		close(ptr[count++]);
}