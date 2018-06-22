/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:02:24 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/22 15:29:54 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	bzero_buffers(t_v_arena *a)
{
	int	i;

	i = -1;
	ft_bzero(&a->nb_instances, sizeof(int) * MAX_PLAYERS);
	while (++i < a->nb_players)
		ft_bzero(a->data_inst[i], sizeof(t_glfloat2) * MEM_SIZE);
}

static void	update_arena_buffers(t_v_arena *a)
{
	int	i;

	i = -1;
	while (++i < a->nb_players)
	{
		glBindBuffer(GL_ARRAY_BUFFER, a->vbos_inst[i]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_glfloat3) * MEM_SIZE,
										a->data_inst[i]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

static void	update_arena_z(t_glfloat3 *a, t_proc *list)
{
	int	i;

	i = -1;
	while (list)
	{
		a[list->pc].z = -10.;
		list = list->next;
	}
	while (++i < MEM_SIZE)
	{
		a[i].z += 0.9;
		a[i].z = ft_fmin(a[i].z, 0.0);
	}
}

void		update_arena(t_v_arena *a, t_data *d)
{
	int	i;

	i = -1;
	bzero_buffers(a);
	pthread_mutex_lock(&g_lock);
	update_arena_z(a->arena_coords, d->proc_list);
	while (++i < MEM_SIZE)
	{
		if (g_arena[i].player)
		{
			a->data_inst[(int)g_arena[i].player - 1]
				[a->nb_instances[(int)g_arena[i].player - 1]++] =
				a->arena_coords[i];
		}
	}
	pthread_mutex_unlock(&g_lock);
	update_arena_buffers(a);
}

void		render_arena(t_v_arena a, t_events e)
{
	int	i;

	i = -1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
