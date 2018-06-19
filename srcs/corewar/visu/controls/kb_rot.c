/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_rot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:13:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/13 15:55:35 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	kb_right(void *v, int type)
{
	((t_visu *)v)->matrices.inc_xpos =
				(type == SDL_KEYDOWN ? INC_POS : 0.);
}

void	kb_left(void *v, int type)
{
	((t_visu *)v)->matrices.inc_xpos =
				(type == SDL_KEYDOWN ? -INC_POS : 0.);
}

void	kb_down(void *v, int type)
{
	((t_visu *)v)->matrices.inc_ypos =
				(type == SDL_KEYDOWN ? -INC_POS : 0.);
}

void	kb_up(void *v, int type)
{
	((t_visu *)v)->matrices.inc_ypos =
				(type == SDL_KEYDOWN ? INC_POS : 0.);
}
