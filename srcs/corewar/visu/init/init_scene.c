/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:03:18 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 00:49:50 by lbelda           ###   ########.fr       */
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

static void			fill_players_on(t_data d, int *pl_on)
{
	int	i;

	i = 0;
	while (d.players_list)
	{
		pl_on[i] = 1;
		i++;
		d.players_list = d.players_list->next;
	}
	while (i < MAX_PLAYERS)
	{
		pl_on[i] = 0;
		i++;
	}
}

void				init_scene(t_visu *v, t_data data)
{
	int	i;

	init_3d_alphabet(v->scene.alphabet_3d);
	v->scene.background = init_background();
	v->scene.all_programs[PROG_BG] = v->scene.background.program;
	v->scene.counters = init_counters(data);
	v->scene.all_programs[PROG_CT] = v->scene.counters.program;
	v->scene.arena = init_arena(data);
	i = -1;
	while (++i < MAX_PLAYERS + 1)
		v->scene.all_programs[i + PROG_PLN] = v->scene.arena.programs[i];
	create_text_data(&v->scene.texts_data);
	init_text(v->scene.texts, v->scene.alphabet_3d,
						data, v->scene.arena.shader_paths);
	i = -1;
	while (++i < TXT_PL1_PROC)
		v->scene.all_programs[i + PROG_TXT] = v->scene.texts[i].program;
	init_text_info(v->scene.texts, v->scene.alphabet_3d,
						data, v->scene.all_programs[PROG_TXT]);
	init_text_info_nb(v->scene.texts, v->scene.all_programs[PROG_TXT]);
	init_ublocks(*v, v->scene.ublocks);
	fill_players_on(data, v->scene.pl_on);
}
