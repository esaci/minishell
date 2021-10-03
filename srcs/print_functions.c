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
	int		count2;

	return (0);
	count = 0;
	while (node && node->right)
	{
		printf("Node n`%d type: %c\n", count, node->type);
		count2 = 0;
		while (node->str[count2])
			printf("%s\n", node->str[count2++]);
		printf("Node n`%d GAUCHE type: %c\n", count, node->left->type);
		count2 = 0;
		while (node->left->str[count2])
			printf("%s\n", node->left->str[count2++]);
		if (node->left->left)
		{
			printf("Node n`%d GAUCHE INPUT type: %c\n", count, node->left->left->type);
			count2 = 0;
			while (node->left->left->str[count2])
				printf("%s\n", node->left->left->str[count2++]);
			printf("Node n`%d GAUCHE OUTPUT type: %c\n", count, node->left->right->type);
			count2 = 0;
			while (node->left->right->str[count2])
				printf("%s\n", node->left->right->str[count2++]);
		}
		node = node->right;
	}
	return (0);
}
