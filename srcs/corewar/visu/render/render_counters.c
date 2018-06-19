/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_counters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:06:44 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/12 17:51:39 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	update_mesh_width(t_counters *c, t_data *d)
{
	(void)c;
	(void)d;
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
