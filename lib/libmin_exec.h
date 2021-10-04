/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin_exec.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:53:25 by esaci             #+#    #+#             */
/*   Updated: 2021/10/04 19:53:27 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBMIN_EXEC_H
# define LIBMIN_EXEC_H

int					exec_input(t_lexer *l);
t_node				*exec_pipe(t_lexerr *l, t_node *n);
int					exec_com(t_lexer *l, t_node *n);
#endif
