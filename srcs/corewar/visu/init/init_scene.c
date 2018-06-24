/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:03:18 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 11:57:34 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define VTX_BG "srcs/corewar/visu/shaders/bg.vtx"
#define FRG_BG "srcs/corewar/visu/shaders/bg.frg"

static void			quad_buffers(t_vec2 *vertices, GLuint *indices)
{
	vertices[0] = (t_vec2){-1.0, -1.0};
	vertices[1] = (t_vec2){1.0, -1.0};
	vertices[2] = (t_vec2){1.0, 1.0};
	vertices[3] = (t_vec2){-1.0, 1.0};
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
}

static t_background	init_background(void)
{
	t_background	bg;
	t_vec2			vertices[4];
	GLuint			indices[4];

	bg.program = build_ogl_program(VTX_BG, FRG_BG);
	quad_buffers(vertices, indices);
	glUseProgram(bg.program);
	glGenVertexArrays(1, &bg.vao);
	glBindVertexArray(bg.vao);
	glGenBuffers(1, &bg.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bg.vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat),
									vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &bg.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bg.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint),
									indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glUseProgram(0);
	return (bg);
}

void				init_scene(t_visu *v, t_data data)
{
	int	i;

	i = -1;
	init_3d_alphabet(v->scene.alphabet_3d);
	v->scene.background = init_background();
	v->scene.all_programs[PROG_BG] = v->scene.background.program;
	v->scene.title = init_title();
	v->scene.all_programs[PROG_TITLE] = v->scene.title.program;
	v->scene.counters = init_counters(data);
	v->scene.all_programs[PROG_CT] = v->scene.counters.program;
	v->scene.arena = init_arena(data);
	while (++i < MAX_PLAYERS)
		v->scene.all_programs[i + PROG_PL1] = v->scene.arena.programs[i];
	init_ublocks(*v, v->scene.ublocks);
}
