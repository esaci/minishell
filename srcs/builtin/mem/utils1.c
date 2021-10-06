/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:15:17 by julespellet       #+#    #+#             */
/*   Updated: 2021/10/04 12:15:22 by julespellet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

void	*ft_alloc(size_t size)
{
	void	*ptr;

	ptr = ft_alloc_mem(size, 0, NULL, 0);
	return (ptr);
}

void	ft_free_ptr(void **addr)
{
	ft_alloc_mem(0, 0, addr, 0);
}

void	ft_destroy_exit(int exit_code)
{
	ft_alloc_mem(0, 1, NULL, exit_code);
}