/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:42:51 by elias             #+#    #+#             */
/*   Updated: 2021/11/03 22:42:55 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin.h"

void	init_infiles(int *fd, int *count, int *oldfd, t_node *n)
{
	*fd = 0;
	*count = 0;
	*oldfd = 0;
	n->archive_fd = n->fd;
}

void	init_outfile(int *fd, int *count, int *oldfd, t_node *n)
{
	*fd = 1;
	*count = 0;
	*oldfd = 0;
	n->archive_fd = n->fd;
}
