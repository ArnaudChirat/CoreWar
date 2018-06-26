/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:23:26 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 19:12:56 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		update_cyc_per_frame(t_visu *v)
{
	v->cyc_per_frame += v->cyc_per_frame_inc;
	v->cyc_per_frame = ft_fclamp(MIN_CPF, MAX_CPF, v->cyc_per_frame);
	v->matrices.speed = (v->pause ? 0. : log10f(v->cyc_per_frame * 0.85 + 1.));
}

void			render(t_visu *v, t_data *d)
{
	while (!v->quit && (v->pause ||
			(int)(1. / v->cyc_per_frame) >= v->frame_since_refresh))
	{
		handle_events(v);
		update_fft(&v->sound);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_cyc_per_frame(v);
		update_clock(v, &v->scene.events);
		update_camera(&v->matrices);
		update_uniforms(*v);
		render_text(v->scene.texts, v->scene.texts_pos,
						v->scene.events, v->scene.pl_on);
		update_arena(&v->scene.arena, d);
		render_arena(v->scene.arena);
		update_counters(&v->scene.counters, d);
		render_counters(v->scene.counters, v->scene.events);
		check_glerror();
		SDL_GL_SwapWindow(v->win);
		v->frame_since_refresh++;
	}
	v->frame_since_refresh = 0;
}
