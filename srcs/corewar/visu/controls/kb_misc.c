/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:13:03 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/02 12:47:28 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	kb_quit(void *v, int type)
{
	if (type == SDL_KEYDOWN)
	{
		((t_visu*)v)->quit = 1;
	}
}

void	kb_debug(void *v, int type)
{
	(void)v;
	(void)type;
}

void	kb_none(void *v, int type)
{
	(void)v;
	(void)type;
}
