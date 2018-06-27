/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps3_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:30:30 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 06:48:03 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ps3_speed_up(void *v, int16_t value)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
			((MULT_CPF - 1.) * (float)value / (float)INT16_MAX) + 1.;
}

void	ps3_speed_down(void *v, int16_t value)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
			((DEMULT_CPF - 1.) * (float)value / (float)INT16_MAX) + 1.;
}

void	ps3_pause(void *v, uint32_t type)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (type == SDL_CONTROLLERBUTTONDOWN && visu->scene.events.phase == PH_GAME)
	{
		visu->pause =
			(visu->pause == 0 ? 1 : 0);
		visu->cyc_per_frame_inc = 1.;
	}
}
