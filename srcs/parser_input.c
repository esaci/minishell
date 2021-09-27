/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:30:33 by esaci             #+#    #+#             */
/*   Updated: 2021/09/25 21:30:34 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libmin.h"

t_token	*parser_next_token(t_token *tok)
{
	t_token		*toktmp;
	TOKENTYPE	tmp;


	if (!tok)
		return (NULL);
	if (tok->type == CHAR_APO)
		tmp = CHAR_APO;
	if (tok->type == CHAR_CHEVD)
		tmp = CHAR_APO | CHAR_CHEVG;
	return (tok->n_token);
	toktmp = tok->n_token;
}

int	parser_lexer(t_lexer *lexer)
{
	t_token		*toktmp;

	toktmp = lexer->tok;
	while (toktmp)
	{
		toktmp->n_token = parser_next_token(toktmp);
		toktmp = toktmp->n_token;
	}
	return (0);
}

t_lexer	*parser_input(t_lexer *lexer)
{
	init_lexer(lexer);
	if (lexer_start(lexer))
		return (NULL);
	if (parser_lexer(lexer))
		return (NULL);
	return (lexer);
}
