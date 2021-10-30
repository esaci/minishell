/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:00:06 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/30 12:16:39 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:12:36 by julpelle          #+#    #+#             */
/*   Updated: 2021/10/29 21:15:24 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libmin_built.h"

void	export_cases_1(t_list *e, char *var, char *ptr)
{
	char	*ptr2;
	char	*ptr3;

	ptr2 = ft_strjoin(var, "=");
	ptr3 = ft_strjoin(ptr2, ptr);
	ft_add_env(ptr3, e);
	free(ptr2);
	free(ptr3);
}

void	export_cases_2(char *arg, t_list *e, char *var, char *ptr)
{
	char	*old_value;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;

	old_value = get_value(arg);
	ptr2 = ft_strjoin(var, "\"");
	ptr3 = ft_substr(old_value, 1, ft_strlen(old_value) - 2);
	ptr4 = ft_strjoin(ptr2, ptr3);
	free(ptr2);
	free(ptr3);
	ptr2 = ft_strjoin(ptr4, ptr);
	ptr3 = ft_strjoin(ptr2, get_value(arg));
	free(ptr4);
	ptr4 = ft_strjoin(ptr3, "\"");
	ft_add_env(ptr4, e);
	free(ptr2);
	free(ptr3);
	free(ptr4);
}

void	export_cases_3(char *arg, t_list *e, char *var)
{
	char	*ptr;
	char	*ptr2;
	char	*ptr3;

	ptr = ft_strjoin(var, "=");
	ptr2 = ft_strjoin(ptr, "\"");
	ptr3 = ft_strjoin(ptr2, get_value(arg));
	free(ptr);
	free(ptr2);
	ptr = ft_strjoin(ptr3, "\"");
	ft_add_env(ptr, e);
	free(ptr);
	free(ptr3);
}

void	export_cases(char *arg, t_list *e)
{
	char	*var;
	char	*ptr;
	char	*test;
	int	flag;

	flag = 0;
	var = get_var(arg);
	ptr = custom_getenv(e, arg, 0);
	test = custom_getenv(e, var, 0);
	ft_del_variable(var, e);
	if (check_all_char(get_value(arg)) == 1 && ft_strncmp(ptr, "", 1))
		flag = 1;
	if (flag == 1)
		export_cases_1(e, var, ptr);
	if (check_variable(arg) == 1 && flag == 0)
		export_cases_2(arg, e, var, ptr);
	else if (check_variable(arg) == 2 && flag == 0)
		export_cases_3(arg, e, var);
	else if (check_variable(arg) == 3 && flag == 0)
		ft_add_env(arg, e);
	free(var);
	free(ptr);
	free(test);
}
