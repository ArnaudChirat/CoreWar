/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:00:33 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 05:40:44 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	init_shader_paths(t_v_arena *a)
{
	a->shader_paths[0] = "srcs/corewar/visu/shaders/player.vtx";
	a->shader_paths[1] = "srcs/corewar/visu/shaders/playern.frg";
	a->shader_paths[2] = "srcs/corewar/visu/shaders/player.vtx";
	a->shader_paths[3] = "srcs/corewar/visu/shaders/player1.frg";
	a->shader_paths[4] = "srcs/corewar/visu/shaders/player.vtx";
	a->shader_paths[5] = "srcs/corewar/visu/shaders/player2.frg";
	a->shader_paths[6] = "srcs/corewar/visu/shaders/player.vtx";
	a->shader_paths[7] = "srcs/corewar/visu/shaders/player3.frg";
	a->shader_paths[8] = "srcs/corewar/visu/shaders/player.vtx";
	a->shader_paths[9] = "srcs/corewar/visu/shaders/player4.frg";
}

static void	init_instances_buffers(t_v_arena *a, int i)
{
	glUseProgram(a->programs[i]);
	glBindVertexArray(a->vaos[i]);
	glBindBuffer(GL_ARRAY_BUFFER, a->vbo_mesh);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, a->vbos_inst[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_glfloat3) * MEM_SIZE,
									NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

static void	init_mesh_buffers(t_v_arena *a)
{
	glBindBuffer(GL_ARRAY_BUFFER, a->vbo_mesh);
	glBufferData(GL_ARRAY_BUFFER, a->mesh.nb_vtx * sizeof(t_glfloat3),
									a->mesh.coords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->ibo_mesh);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			a->mesh.nb_indices * sizeof(GLuint),
			a->mesh.indices_uni, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void	gen_buffers(t_v_arena *a, int n)
{
	glGenVertexArrays(n, a->vaos);
	glGenBuffers(n, a->vbos_inst);
	glGenBuffers(1, &a->vbo_mesh);
	glGenBuffers(1, &a->ibo_mesh);
}

t_v_arena	init_arena(t_data data)
{
	t_v_arena	a;
	int			i;

	i = -1;
	ft_bzero(&a, sizeof(t_v_arena));
	a.winner = -1;
	init_arena_data(&a, data);
	gen_buffers(&a, MAX_PLAYERS + 1);
	init_shader_paths(&a);
	a.mesh = create_arena_mesh();
	a.nb_players = data.nbr_player;
	init_mesh_buffers(&a);
	while (++i < MAX_PLAYERS + 1)
	{
		a.programs[i] = build_ogl_program(a.shader_paths[i * 2],
										a.shader_paths[i * 2 + 1]);
		init_instances_buffers(&a, i);
	}
	return (a);
}
