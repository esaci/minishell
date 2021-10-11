/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:27:01 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/07 08:46:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lib_jules.h"

void    ft_delete_variable(char *variable)
{
    t_list  *env;
    t_list  *new_env;

    env = ft_getallenv();
    new_env = NULL;
    while (env)
    {
        if (ft_strlen(env->content) > ft_strlen(variable))
        {
            printf("Content : %s\nVariable : %s\n\n", env->content, variable);
            printf("Comp : %d\n\n", ft_strncmp(env->content, variable, ft_strlen(variable)));
            if (ft_strncmp(env->content, variable, ft_strlen(variable) == 0)
                && *(env->content + ft_strlen(variable) + 1) == '=')
            {
                printf("In Boucle\n");
                if (new_env)
                    new_env->next = env->next;
                else
                {
                    ft_envp(NULL, NULL, env->next);
                    printf(RED"Deleted variable\n"RESET);
                }
                return ;
            }
        }
        new_env = env;
        env = env->next;
    }
    return ;
}