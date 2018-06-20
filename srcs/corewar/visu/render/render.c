/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:23:26 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 17:17:57 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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
	int	prog;

	if (e.phase == PH_INTRO)
	{
		prog = (int)((float)t.mesh.nb_indices * (e.intro * 1.5));
		prog = prog > t.mesh.nb_indices ? t.mesh.nb_indices : prog;
		glUseProgram(t.program);
		glBindVertexArray(t.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t.ibo);
		glDrawElements(GL_TRIANGLES, prog, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

static void	update_vm_sleep(t_visu *v)
{
	v->cyc_sleep += v->cyc_sleep_inc;
	ft_clamp(MIN_SLEEP, MAX_SLEEP, v->cyc_sleep);
}

int			render(t_visu *v)
{
	v->scene.events = init_clock();
	while (!v->quit)
	{
		handle_events(v);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_vm_sleep(v);
		update_clock(&v->scene.events);
		update_camera(&v->matrices);
		update_uniforms(v->scene, v->matrices);
		render_background(v->scene.background);
		glClear(GL_DEPTH_BUFFER_BIT);
		render_title(v->scene.title, v->scene.events);
		update_arena(&v->scene.arena);
		render_arena(v->scene.arena, v->scene.events);
		update_counters(&v->scene.counters, v->data);
		render_counters(v->scene.counters, v->scene.events);
		check_glerror();
		SDL_GL_SwapWindow(v->win);
	}
	return (0);
}