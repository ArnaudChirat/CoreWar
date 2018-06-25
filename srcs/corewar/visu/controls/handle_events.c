/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:12:58 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 17:08:16 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_controls.h"
#include "visu.h"

static void	search_kb_lookup(t_visu *v, SDL_Keycode sym, int type)
{
	int	i;

	i = -1;
	while (++i < KB_MAX)
	{
		if (v->controls.kb_lookup[i].sym == sym)
		{
			v->controls.kb_lookup[i].func(v, type);
			break ;
		}
	}
}

static void	search_ps3_lookup(t_visu *v, uint8_t axis, int16_t value)
{
	int	i;

	i = -1;
	value = (iabs(value) > 3500 ? value : 0);
	while (++i < PS3_MAX)
	{
		if (v->controls.ps3_lookup[i].axis == axis)
		{
			v->controls.ps3_lookup[i].func(v, value);
			break ;
		}
	}
}

void		handle_events(t_visu *v)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			search_kb_lookup(v, event.key.keysym.sym, event.type);
		else if (event.type == SDL_CONTROLLERAXISMOTION)
			search_ps3_lookup(v, event.caxis.axis, event.caxis.value);
	}
}
