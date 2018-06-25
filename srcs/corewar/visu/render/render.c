/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:23:26 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 14:11:20 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
   static void	render_background(t_background bg)
   {
   glUseProgram(bg.program);
   glBindVertexArray(bg.vao);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bg.ibo);
   glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   glUseProgram(0);
   }

   static void	render_title(t_title t, t_events e)
   {
   if (e.phase == PH_INTRO)
   {
   glUseProgram(t.program);
   glBindVertexArray(t.vao);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t.ibo);
   glDrawElements(GL_TRIANGLES, t.mesh.nb_indices, GL_UNSIGNED_INT, NULL);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   glUseProgram(0);
   }
   }
   */

static void	update_cyc_per_frame(t_visu *v)
{
	v->cyc_per_frame += v->cyc_per_frame_inc;
	v->cyc_per_frame = ft_fclamp(MIN_CPF, MAX_CPF, v->cyc_per_frame);
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
		//render_background(v->scene.background);
		glClear(GL_DEPTH_BUFFER_BIT);
		//render_title(v->scene.title, v->scene.events);
		render_text(v->scene.texts, v->scene.events);
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
