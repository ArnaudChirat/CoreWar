/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:02:24 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/12 17:10:19 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	bzero_buffers(t_v_arena *a)
{
	int	i;

	i = -1;
	while (++i < a->nb_players)
		ft_bzero(a->data_inst[i], sizeof(t_glfloat2) * MEM_SIZE);
}

void	update_arena(t_v_arena *a)
{
	int	i;

	i = -1;
	ft_bzero(&a->nb_instances, sizeof(int) * MAX_PLAYERS);
	bzero_buffers(a);
	while (++i < MEM_SIZE)
	{
		if (g_arena[i].player)
			a->data_inst[(int)g_arena[i].player - 1]
				[a->nb_instances[(int)g_arena[i].player - 1]++]
			= a->arena_coords[i];
	//printf("c%d: x%f y%f\n", i, a->arena_coords[i].x, a->arena_coords[i].y);
	}
	i = -1;
	while (++i < a->nb_players)
	{
		glBindBuffer(GL_ARRAY_BUFFER, a->vbos_inst[i]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_glfloat2) * MEM_SIZE,
										a->data_inst[i]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void	render_arena(t_v_arena a, t_events e)
{
	int	i;

	i = -1;
	if (e.phase == PH_GAME || e.phase == PH_FINAL)
		while (++i < a.nb_players)
		{
			glUseProgram(a.programs[i]);
			glBindVertexArray(a.vaos[i]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a.ibo_mesh);
			glDrawElementsInstanced(GL_TRIANGLE_FAN, a.mesh.nb_indices,
					GL_UNSIGNED_INT, NULL, a.nb_instances[i]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
}
