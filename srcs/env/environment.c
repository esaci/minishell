/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:24:28 by Jules             #+#    #+#             */
/*   Updated: 2021/11/03 02:46:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

t_list	*ft_envp(char *envp[], char *content, t_list *v_env)
{
	if (envp != NULL && !v_env)
		v_env = ft_tab_to_lst(envp);
	else if (content != NULL && v_env)
		ft_lst_pushback(&v_env, content);
	return (v_env);
}

char	*custom_getenv(t_list *l, char *ptr, int mode)
{
	while (l)
	{
		if (l->content && !ft_memcmp(l->content, ptr, ft_strlen(ptr)))
		{
			if (l->content[ft_strlen(ptr)] == '=' && !mode)
				return (correct_path(copieur(l->content + ft_strlen(ptr) + 1)));
			if (l->content[ft_strlen(ptr)] == '=')
				return (copieur(l->content + ft_strlen(ptr) + 1));
		}
		l = l->next;
	}
	return (copieur(""));
}

char	*clear_apo(char *ptr)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (ptr[count])
	{
		ptr[count] = ptr[count + count2];
		if (ptr[count] == '=')
			count2 = 1;
		count++;
	}
	if (count2)
		ptr[count - 2] = 0;
	else
		ptr[count] = 0;
	return (ptr);
}

char	**generate_custom_envp(t_list *v_env)
{
	int		count;
	t_list	*tmp;
	char	**ptr;
	char	*str;

	count = utils_strlen_env(v_env);
	ptr = malloc(sizeof(char *) * (count + 3));
	if (!ptr)
		return (NULL);
	ptr[count] = NULL;
	tmp = v_env;
	count = 0;
	while (tmp)
	{
		str = copieur(tmp->content);
		ptr[count++] = clear_apo(str);
		tmp = tmp->next;
	}
	return (ptr);
}
