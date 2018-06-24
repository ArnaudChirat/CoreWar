/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_counters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:51:49 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 16:01:55 by lbelda           ###   ########.fr       */
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

t_counters	init_counters(t_data d)
{
	t_counters	c;

	ft_bzero(&c, sizeof(t_counters));
	c.program = build_ogl_program(VTX_CT, FRG_CT);
	gen_buffers(&c);
	c.nb_players = d.nbr_player;
	c.mesh = create_counter_mesh();
	glUseProgram(c.program);
	glBindVertexArray(c.vao);
	init_mesh_buffers(&c);
	glBindVertexArray(0);
	glUseProgram(0);
	return (c);
}
