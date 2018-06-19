/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:12:58 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/02 12:46:59 by lbelda           ###   ########.fr       */
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

void		handle_events(t_visu *v)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			search_kb_lookup(v, event.key.keysym.sym, event.type);
	}
}
