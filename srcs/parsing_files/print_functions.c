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

#include "../../lib/libmin.h"

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
		print_custom("type: ", 1, 1, 0);
		write(1, &t->type, 1);
		write(1, "  ", 2);
		write(1, "|", 1);
		write(1, l->buffer[count], ft_strlen(l->buffer[count]));
		write(1, "|", 1);
		write(1, "\n", 1);
		t = t->n_token;
		count++;
	}
	return (0);
}

int	print_str_node(t_node *n, char *str, int count2)
{
	int		count;
	char	*ptr;

	if (count2)
	{
		ptr = ft_itoa(count2);
		print_custom(ptr, 1, 1, 0);
		free(ptr);
	}
	if (str)
		print_custom(str, 1, 1, 0);
	count = 0;
	while (n->str && n->str[count])
		count += print_custom(n->str[count], 1, 1, 1);
	return (1);
}

int	print_node(t_node *node)
{
	int		count;
	char	*ptr;

	count = 1;
	while (node)
	{
		if (node->type == NODE_FILEOUT)
			break ;
		write(1, &node->type, 1);
		print_str_node(node, " Node :\n", count);
		if (!node->left)
			break ;
		if (node->left->type != NODE_FILEIN && node->left->type != NODE_DFILEIN)
		{
			write(1, "{\n", 2);
			write(1, &node->left->type, 1);
			print_str_node(node->left, " Commande a Gauche :\n", count);
			print_str_node(node->left->left, " Infile Commande :\n", count);
			print_str_node(node->left->right, " Outfile Commande :\n", count);
			write(1, "}\n", 2);
		}
		else
			print_str_node(node->left, " Infile Commande :\n", count);
		if (node->right->type == NODE_FILEOUT || node->right->type == NODE_DFILEOUT)
		{
			print_str_node(node->right, " Outfile Commande :\n", count);
			node = NULL;
		}
		else
			node = node->right;
		count++;
		if (node)
		{
			ptr = ft_itoa(count);
			print_custom(ptr, 1, 1, 0);
			free(ptr);
			print_custom(" Droite Pipe/Commande:", 1, 1, 1);
		}
	}
	return (0);
}

int	print_env(t_lexer *l)
{
	int		count;
	char	*ptr;

	count = 0;
	while (l->buffer && l->buffer[count])
	{
		if (l->buffer[count][0] == '$')
			break;
		count++;
	}
	if (l->buffer && l->buffer[count])
	{
		ptr = custom_getenv(l->envp, (l->buffer[count]) + 1);
		printf("l'environnement de %s : %s\n", (l->buffer[count]) + 1, ptr);
	}
	return (0);
}

void full_print(char **str)
{
	int count;

	count = 0;\
	if (!str || !str[0])
	{
		print_custom("Input: VIDE", 1, 1, 1);
		return ;
	}
	while (str && str[count])
	{
		print_custom("Input: ", 1, 1, 0);
		print_custom(str[count], 1, 1, 1);
		count++;
	}
	print_custom("FIN", 1, 1, 1);
}
