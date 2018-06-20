/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_counters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:06:44 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 18:08:39 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	update_mesh_width(t_counters *c, t_data *d)
{
	c->mesh.coords[0].x = CT_WIDTH * (1. - ((float)d->cy / (float)d->ctd));
	c->mesh.coords[1].x = c->mesh.coords[0].x;
	c->mesh.coords[2].x = c->mesh.coords[0].x;
	c->mesh.coords[3].x = c->mesh.coords[0].x;
	glBindBuffer(GL_ARRAY_BUFFER, c->vbos[VBO_CT_MESH]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_glfloat3) * 4,
									c->mesh.coords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		update_counters(t_counters *c, t_data *d)
{
	int	i;

	update_mesh_width(c, d);
	i = -1;
	while (++i < c->nb_players)
	{
	}
}

void		render_counters(t_counters c, t_events e)
{
	if (e.phase == PH_GAME || e.phase == PH_FINAL)
	{
		glUseProgram(c.program);
		glBindVertexArray(c.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c.ibo);
		glDrawElementsInstanced(GL_TRIANGLES, c.mesh.nb_indices,
				GL_UNSIGNED_INT, NULL, c.nb_players);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}
