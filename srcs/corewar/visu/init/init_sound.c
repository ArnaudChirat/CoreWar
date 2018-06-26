/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 09:30:05 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 16:01:00 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_sound.h"

static void	system_init(t_sound *sound)
{
	FMOD_RESULT	err;

	if ((err = FMOD_System_Create(&(sound->system))) != FMOD_OK)
		error_exit("FMOD Failed to create system");
	if ((err = FMOD_System_Init(sound->system, 512,
					FMOD_INIT_NORMAL, 0)) != FMOD_OK)
		error_exit("FMOD Failed to init system");
}

static int	channel_init(t_sound *sound, char *file)
{
	FMOD_RESULT	err;
	int			i;

	i = 0;
	if ((err = FMOD_System_CreateStream(sound->system, file,
			FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &(sound->song))) != FMOD_OK)
		return (0);
	if ((err = FMOD_System_PlaySound(sound->system, sound->song,
					0, 1, &sound->channel)) != FMOD_OK)
		error_exit("FMOD Failed to play audio");
	if ((err = FMOD_Sound_GetFormat(sound->song, 0, 0,
					&sound->data.numchannels, 0)) != FMOD_OK)
		return (0);
	return (1);
}

static void	dsp_init(t_sound *sound)
{
	FMOD_RESULT	err;
	int			i;

	i = 0;
	if ((err = FMOD_System_CreateDSPByType(sound->system,
					FMOD_DSP_TYPE_FFT, &sound->fft)) != FMOD_OK)
		error_exit("FMOD Failed to create DSP");
	if ((err = FMOD_DSP_SetParameterInt(sound->fft,
					FMOD_DSP_FFT_WINDOWSIZE, FFT_SIZE)) != FMOD_OK)
		error_exit("FMOD Failed to configure DSP");
	if ((err = FMOD_Channel_AddDSP(sound->channel, 0,
					sound->fft)) != FMOD_OK)
		error_exit("FMOD Failed to connect DSP");
}

t_sound		init_sound(void)
{
	t_sound	s;

	ft_bzero(&s, sizeof(t_sound));
	if (FMOD_Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR,
							FMOD_DEBUG_MODE_TTY, 0, NULL) != FMOD_OK)
		error_exit("FMOD Failed to setup debug mode");
	system_init(&s);
	if (channel_init(&s, SONG_PATH))
	{
		s.mode = S_ON;
		dsp_init(&s);
	}
	else
	{
		s.mode = S_OFF;
		FMOD_System_Release(s.system);
	}
	return (s);
}
