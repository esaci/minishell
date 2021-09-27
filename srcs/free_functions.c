/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:12:06 by esaci             #+#    #+#             */
/*   Updated: 2021/09/27 19:12:08 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

int	free_lexer_tokens(t_lexer *lexer)
{
	t_token		*ltmp;
	t_token		*ltmp2;
	int			count;

	count = 0;
	if (!lexer)
		return (count);
	ltmp = lexer->tok;
	while (ltmp)
	{
		ltmp2 = ltmp->n_token;
		free(ltmp);
		ltmp = ltmp2;
		count++;
	}
	return (count);
}
