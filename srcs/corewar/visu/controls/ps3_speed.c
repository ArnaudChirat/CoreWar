/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps3_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:30:30 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 17:14:21 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ps3_speed_up(void *v, int16_t value)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
			INC_CPF * (float)value / (float)INT16_MAX;
}

void	ps3_speed_down(void *v, int16_t value)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
			-INC_CPF * (float)value / (float)INT16_MAX;
}
