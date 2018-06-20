/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:13:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 17:23:00 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	kb_speed_up(void *v, int type)
{
	((t_visu *)v)->cyc_sleep_inc =
				(type == SDL_KEYDOWN ? -INC_SLEEP : 0.);
}

void	kb_speed_down(void *v, int type)
{
	((t_visu *)v)->cyc_sleep_inc =
				(type == SDL_KEYDOWN ? INC_SLEEP : 0.);
}

void	kb_pause(void *v, int type)
{
	(void)v;
	(void)type;
}
