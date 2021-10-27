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

void	handler_son(int num);
void	signal_wait_input(void);
void	get_signal_child(void);
void	signal_ignore(void);
void	signal_default(void);

#endif
