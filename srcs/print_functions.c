/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:58:22 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 18:58:23 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	print_custom(char *str, int fd, int exit_code, int saut_ligne)
{
	write(fd, str, ft_strlen(str));
	if (saut_ligne)
		write(fd, "\n", 1);
	return (exit_code);
}

int	print_tokens(t_lexer *l)
{
	t_token *t;
	int count;

	count = 0;
	t =  l->tok;
	while (t)
	{
		write(1, "|", 1);
		write(1, l->buffer[count], ft_strlen(l->buffer[count]));
		write(1, "|", 1);
		write(1, "\n", 1);
		t = t->n_token;
		count++;
	}
	return (0);
}

int	print_node(t_node *node)
{
	int		count;
	t_node	*node2;

	write(1, &node->type, 1);
	write(1, "\n", 1);
	node2 = node;
	if (node->type == NODE_PIPE)
		node = node->left;
	if (node->type != NODE_PATHCOM)
		return (0);
	count = 0;
	while (node->str[count])
		count += print_custom(node->str[count], 1, 1, 2);
	count = 0;
	while (node->left->str[count])
		count += print_custom(node->left->str[count], 1, 1, 2);
	count = 0;
	while (node->right->str[count])
		count += print_custom(node->right->str[count], 1, 1, 2);
	node = node2->right;
	if (node2->type == NODE_PIPE)
		print_node(node2->right);
	return (0);
}
