/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:16:07 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 06:50:11 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_controls.h"
#include "libft.h"

static void	init_kb_lookup(t_kb_lookup *kb)
{
	kb[KB_RIGHT] = (t_kb_lookup){SDLK_RIGHT, &kb_speed_up};
	kb[KB_LEFT] = (t_kb_lookup){SDLK_LEFT, &kb_speed_down};
	kb[KB_DOWN] = (t_kb_lookup){SDLK_DOWN, &kb_none};
	kb[KB_UP] = (t_kb_lookup){SDLK_UP, &kb_none};
	kb[KB_D] = (t_kb_lookup){SDLK_d, &kb_right};
	kb[KB_A] = (t_kb_lookup){SDLK_a, &kb_left};
	kb[KB_S] = (t_kb_lookup){SDLK_s, &kb_down};
	kb[KB_W] = (t_kb_lookup){SDLK_w, &kb_up};
	kb[KB_P] = (t_kb_lookup){SDLK_p, &kb_none};
	kb[KB_SPACE] = (t_kb_lookup){SDLK_SPACE, &kb_pause};
	kb[KB_ESCAPE] = (t_kb_lookup){SDLK_ESCAPE, &kb_quit};
}

static void	init_ps3_lookup(t_ps3_a_lookup *ps3_axis,
							t_ps3_b_lookup *ps3_button)
{
	ps3_axis[PS3_AXIS_LEFTX] =
			(t_ps3_a_lookup){SDL_CONTROLLER_AXIS_LEFTX, &ps3_xtrs};
	ps3_axis[PS3_AXIS_LEFTY] =
			(t_ps3_a_lookup){SDL_CONTROLLER_AXIS_LEFTY, &ps3_ytrs};
	ps3_axis[PS3_AXIS_TRIGGERLEFT] =
			(t_ps3_a_lookup){SDL_CONTROLLER_AXIS_TRIGGERLEFT, &ps3_speed_down};
	ps3_axis[PS3_AXIS_TRIGGERRIGHT] =
			(t_ps3_a_lookup){SDL_CONTROLLER_AXIS_TRIGGERRIGHT, &ps3_speed_up};
	ps3_button[PS3_BUT_X] =
			(t_ps3_b_lookup){SDL_CONTROLLER_BUTTON_A, &ps3_pause};
	ps3_button[PS3_BUT_START] =
			(t_ps3_b_lookup){SDL_CONTROLLER_BUTTON_START, &ps3_exit};
}

t_controls	init_controls(void)
{
	t_controls	c;

	ft_bzero(&c, sizeof(t_controls));
	init_kb_lookup(c.kb_lookup);
	init_ps3_lookup(c.ps3_a_lookup, c.ps3_b_lookup);
	c.ps3_id = SDL_GameControllerOpen(0);
	return (c);
}
