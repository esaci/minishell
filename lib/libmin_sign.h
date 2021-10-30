/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmin_sign.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:03:22 by elias             #+#    #+#             */
/*   Updated: 2021/10/27 17:03:23 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMIN_SIGN_H
# define LIBMIN_SIGN_H

void	signal_wait_input(void);
void	signal_wait_command(void);
void	signal_wait_heredoc(void);
void	signal_default(void);
void	handler_child_sigquit(int num);
void	handler_parent(int num);
void	handler_parent_heredoc(int num);
void	handler_parent_muted(int num);

#endif
