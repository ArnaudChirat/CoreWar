/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:40:20 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 11:34:21 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_sound.h"

void	launch_music(t_sound *sound)
{
	if (FMOD_Channel_SetPaused(sound->channel, 0) != FMOD_OK)
		error_exit("FMOD Failed to play audio");
}
