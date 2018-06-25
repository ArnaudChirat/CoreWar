/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:13:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 12:09:14 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	kb_speed_up(void *v, int type)
{
	((t_visu *)v)->cyc_per_frame_inc =
				(type == SDL_KEYDOWN ? INC_CPF : 0.);
}

void	kb_speed_down(void *v, int type)
{
	((t_visu *)v)->cyc_per_frame_inc =
				(type == SDL_KEYDOWN ? -INC_CPF : 0.);
}

void	kb_pause(void *v, int type)
{
	(void)v;
	(void)type;
}
