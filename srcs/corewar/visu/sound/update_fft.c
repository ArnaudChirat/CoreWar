/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:12:07 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/23 12:23:09 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_sound.h"

static void		refresh_audio(t_sound *sound)
{
	FMOD_RESULT	err;

	if ((err = FMOD_System_Update(sound->system)) != FMOD_OK)
		error_exit("Failed to update FMOD System");
	if ((err = FMOD_DSP_GetParameterData(sound->fft,
					FMOD_DSP_FFT_SPECTRUMDATA, (void*)&sound->data.spec,
					0, 0, 0)))
		error_exit("");
}

static float	get_bins(float *bins, size_t a, size_t b)
{
	size_t	i;
	float	total;

	i = a;
	total = 0;
	while (i < b)
	{
		total += bins[i];
		i++;
	}
	return (total);
}

void			update_fft(t_sound *s)
{
	if (s->mode == S_ON)
	{
		refresh_audio(s);
		s->data.bass = get_bins(s->data.spec->spectrum[0], 2, 4);
	}
}
