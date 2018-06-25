/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps3_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:30:30 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 17:16:24 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ps3_xtrs(void *v, int16_t value)
{
	((t_visu *)v)->matrices.inc_xpos =
					-INC_POS * (float)value / (float)INT16_MAX;
}

void	ps3_ytrs(void *v, int16_t value)
{
	((t_visu *)v)->matrices.inc_ypos =
					-INC_POS * (float)value / (float)INT16_MAX;
}
