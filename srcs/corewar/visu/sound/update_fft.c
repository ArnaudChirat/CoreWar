/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:12:07 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 17:11:48 by lbelda           ###   ########.fr       */
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

static float	get_smoothed_bass(float raw, float prec)
{
	float		new;
	static int	flag = 0;

	if (!flag)
	{
		if (prec == 0. && raw > prec + 0.10)
		{
			new = prec + .30;
			flag = 1;
		}
		else
			new = prec - .03;
	}
	else
	{
		new = prec + .18;
		flag = 0;
	}
	new = ft_fmax(new, 0.);
	return (new);
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
		if (s->data.spec->spectrum[0])
		{
			s->data.raw_bass = get_bins(s->data.spec->spectrum[0], 0, 2);
			s->data.bass = get_smoothed_bass(s->data.raw_bass, s->data.bass);
		}
	}
}
