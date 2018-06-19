/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_common.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:54:16 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/02 13:25:48 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_COMMON_H
# define V_COMMON_H

# include "unistd.h"
# include "fcntl.h"
# include "libft.h"
# include "ft_printf.h"

void	m_pro(int ret);
void	m_pro_null(void *ret);
void	free_pro(void **ptr);

void	error_exit(const char *str);

#endif
