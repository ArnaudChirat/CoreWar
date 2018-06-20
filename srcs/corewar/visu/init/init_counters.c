/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_counters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:51:49 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 13:49:58 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define VTX_CT "srcs/corewar/visu/shaders/ct.vtx"
#define FRG_CT "srcs/corewar/visu/shaders/ct.frg"

#define LR_SPACE 110.
#define UD_SPACE 50.

static void	gen_buffers(t_counters *c)
{
	glGenVertexArrays(1, &c->vao);
	glGenBuffers(VBO_CT_MAX, c->vbos);
	glGenBuffers(1, &c->ibo);
}

static void	init_instance_buffers(t_counters *c)
{
	glBindBuffer(GL_ARRAY_BUFFER, c->vbos[VBO_CT_INST]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_glfloat3) * MAX_PLAYERS,
									c->inst_coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, c->vbos[VBO_CT_STATE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_glfloat3) * MAX_PLAYERS,
									c->inst_coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(2, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void	init_mesh_buffers(t_counters *c)
{
	glBindBuffer(GL_ARRAY_BUFFER, c->vbos[VBO_CT_MESH]);
	glBufferData(GL_ARRAY_BUFFER, c->mesh.nb_vtx * sizeof(t_glfloat3),
									c->mesh.coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			c->mesh.nb_indices * sizeof(GLuint),
			c->mesh.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void	init_inst_coords(t_glfloat3 *coords)
{
	coords[P_1] = (t_glfloat3){-LR_SPACE, UD_SPACE, -10.};
	coords[P_2] = (t_glfloat3){LR_SPACE, UD_SPACE, -10.};
	coords[P_3] = (t_glfloat3){-LR_SPACE, -UD_SPACE, -10.};
	coords[P_4] = (t_glfloat3){LR_SPACE, -UD_SPACE, -10.};
}

t_counters	init_counters(t_data d)
{
	t_counters	c;

	ft_bzero(&c, sizeof(t_counters));
	c.program = build_ogl_program(VTX_CT, FRG_CT);
	gen_buffers(&c);
	c.nb_players = d.nbr_player;
	c.mesh = create_counter_mesh();
	init_inst_coords(c.inst_coords);
	glUseProgram(c.program);
	glBindVertexArray(c.vao);
	init_mesh_buffers(&c);
	init_instance_buffers(&c);
	glBindVertexArray(0);
	glUseProgram(0);
	return (c);
}
