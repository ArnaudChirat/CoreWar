/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:16:07 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 16:45:36 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_controls.h"
#include "libft.h"

t_controls	init_controls(void)
{
	t_controls	c;

	ft_bzero(&c, sizeof(t_controls));
	c.kb_lookup[KB_RIGHT] = (t_kb_lookup){SDLK_RIGHT, &kb_speed_up};
	c.kb_lookup[KB_LEFT] = (t_kb_lookup){SDLK_LEFT, &kb_speed_down};
	c.kb_lookup[KB_DOWN] = (t_kb_lookup){SDLK_DOWN, &kb_none};
	c.kb_lookup[KB_UP] = (t_kb_lookup){SDLK_UP, &kb_none};
	c.kb_lookup[KB_D] = (t_kb_lookup){SDLK_d, &kb_right};
	c.kb_lookup[KB_A] = (t_kb_lookup){SDLK_a, &kb_left};
	c.kb_lookup[KB_S] = (t_kb_lookup){SDLK_s, &kb_down};
	c.kb_lookup[KB_W] = (t_kb_lookup){SDLK_w, &kb_up};
	c.kb_lookup[KB_P] = (t_kb_lookup){SDLK_p, &kb_none};
	c.kb_lookup[KB_SPACE] = (t_kb_lookup){SDLK_SPACE, &kb_pause};
	c.kb_lookup[KB_ESCAPE] = (t_kb_lookup){SDLK_ESCAPE, &kb_quit};
	return (c);
}
