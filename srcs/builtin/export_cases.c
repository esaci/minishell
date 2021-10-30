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

int	check_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i] && arg[i] != '=')
		i++;
	if (!i)
		return (1);
	return (0);
}

void	export_exist_equal(t_list *e, char *var, char *ptr)
{
	char	*ptr2;
	char	*ptr3;

	ptr2 = ft_strjoin(var, "=");
	ptr3 = ft_strjoin(ptr2, ptr);
	ft_add_env(ptr3, e);
	free(ptr2);
	free(ptr3);
}

void	export_with_plus(char *complete_arg, t_list *e, char *var, char *old_value)
{
	char	*ptr2;
	char	*ptr3;

	print_custom("case2", 1, 1, 1);
	print_custom(old_value, 1, 1, 1);
	ptr3 = ft_strjoin(var, "=");
	ptr2 = ft_strjoin(ptr3, "\"");
	free(ptr3);
	ptr3 = ft_strjoin(ptr2, old_value);
	free(ptr2);
	ptr2 = ft_strjoin(ptr3, get_value(complete_arg));
	free(ptr3);
	ptr3 = ft_strjoin(ptr2, "\"");
	free(ptr2);
	print_custom(ptr3, 1, 1, 1);
	ft_add_env(ptr3, e);
	free(ptr3);
}

void	export_exist_empty(char *arg, t_list *e, char *var)
{
	char	*ptr;
	char	*ptr2;
	char	*ptr3;

	print_custom("case3", 1, 1, 1);
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
	int		flag;

	flag = 0;
	var = get_var(arg);
	ptr = custom_getenv(e, var, 0);
	ft_del_variable(var, e);
	if (check_all_char(get_value(arg)) == 1 && ft_strncmp(ptr, "", 1))
		flag = 1;
	if (flag == 1)
		export_exist_equal(e, var, ptr);
	if (check_variable(arg) == 1 && flag == 0)
		export_with_plus(arg, e, var, ptr);
	else if (check_variable(arg) == 2 && flag == 0)
		export_exist_empty(arg, e, var);
	else if (check_variable(arg) == 3 && flag == 0)
		ft_add_env(arg, e);
	free(var);
	free(ptr);
}
