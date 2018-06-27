/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 11:38:32 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 08:24:25 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	free_sound(t_sound *sound)
{
	FMOD_RESULT	err;
	int			i;

	err = FMOD_OK;
	i = -1;
	if (sound->mode == S_ON)
	{
		err |= FMOD_Channel_RemoveDSP(sound->channel, sound->fft);
		err |= FMOD_DSP_Release(sound->fft);
		err |= FMOD_Channel_Stop(sound->channel);
		err |= FMOD_Sound_Release(sound->song);
		err |= FMOD_System_Release(sound->system);
		if (err != FMOD_OK)
			ft_putendl("smthing wrong");
	}
}

void		ft_free_visu(t_visu *v, t_data d)
{
	if (d.flag_v)
	{
		free_scene(&v->scene);
		free_sound(&v->sound);
		SDL_PumpEvents();
		SDL_FlushEvents(0, SDL_LASTEVENT);
		while (SDL_PollEvent(NULL))
		{
		}
		SDL_GameControllerClose(v->controls.ps3_id);
		SDL_GL_DeleteContext(v->context);
		SDL_DestroyWindow(v->win);
		SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
		SDL_Quit();
	}
	free_pro((void**)&v);
}
