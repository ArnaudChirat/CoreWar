/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:13:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 06:33:51 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	kb_speed_up(void *v, int type)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
				(type == SDL_KEYDOWN ? MULT_CPF : 1.);
}

void	kb_speed_down(void *v, int type)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (!visu->pause)
		visu->cyc_per_frame_inc =
				(type == SDL_KEYDOWN ? DEMULT_CPF : 1.);
}

void	kb_pause(void *v, int type)
{
	t_visu	*visu;

	visu = (t_visu*)v;
	if (type == SDL_KEYDOWN && visu->scene.events.phase == PH_GAME)
	{
		visu->pause =
			(visu->pause == 0 ? 1 : 0);
		visu->cyc_per_frame_inc = 1.;
	}
}
