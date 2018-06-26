/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:07:22 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 14:54:08 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_common.h"

void	m_pro(int ret)
{
	if (ret == -1)
		error_exit("malloc error");
}

void	m_pro_null(void *ret)
{
	if (!ret)
		error_exit("malloc error");
}

void	free_pro(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
