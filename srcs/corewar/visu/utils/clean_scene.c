/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:10:18 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 16:02:51 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	free_arena(t_v_arena *arena)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS + 1)
	{
		glDeleteBuffers(1, &arena->vbos_inst[i]);
		free_pro((void**)&arena->data_inst[i]);
		glDeleteProgram(arena->programs[i]);
	}
	glDeleteBuffers(1, &arena->vbo_mesh);
	glDeleteBuffers(1, &arena->ibo_mesh);
	free_mesh(&arena->mesh);
	free_pro((void**)&arena->arena_coords);
}

static void	free_counters(t_counters *c)
{
	glDeleteBuffers(VBO_CT_MAX, c->vbos);
	glDeleteBuffers(1, &c->ibo);
	glDeleteProgram(c->program);
	free_mesh(&c->mesh);
}

void		free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	free_arena(&scene->arena);
	free_counters(&scene->counters);
	while (++i < TXT_MAX)
		free_text_field(&scene->texts[i]);
	i = -1;
	while (++i < A_MAX)
		free_mesh(&scene->alphabet_3d[i]);
}
