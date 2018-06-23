/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_sound.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 09:30:36 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/23 10:02:20 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_SOUND_H
# define V_SOUND_H

# include "fmod.h"
# include "libft.h"
# include "v_common.h"

# define SONG_PATH "res/music/perfect_way.mp3"
# define FFT_SIZE 1024

enum			e_soundmode
{
	S_ON,
	S_OFF
};

typedef struct	s_sound_data
{
	int						numchannels;
	FMOD_DSP_PARAMETER_FFT	*spec;
}				t_sound_data;

typedef struct	s_sound
{
	FMOD_SYSTEM		*system;
	FMOD_SOUND		*song;
	FMOD_CHANNEL	*channel;
	FMOD_DSP		*fft;
	t_sound_data	data;
	int				mode;
}				t_sound;

t_sound			init_sound(void);

#endif
