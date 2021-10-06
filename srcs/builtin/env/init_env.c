/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julespelletier <julespelletier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:36:15 by Jules             #+#    #+#             */
/*   Updated: 2021/10/04 13:47:37 by julespellet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

void	ft_init_env(char *envp[])
{
	printf("Check INIT\n");
	ft_envp(envp, NULL, NULL);
}

void	ft_add_env(char *to_add)
{
	ft_envp(NULL, to_add, NULL);
}

t_list	**ft_getaddenv(void)
{
	return (ft_envp(NULL, NULL, NULL));
}

t_list	*ft_getallenv(void)
{
	printf("Check GET ENV\n");
	return (*ft_envp(NULL, NULL, NULL));
}