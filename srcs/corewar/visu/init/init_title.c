/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_title.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 13:52:53 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 11:27:21 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "v_obj_parser.h"

#define TITLE_OBJ "res/models/title.obj"
#define VTX_TITLE "srcs/corewar/visu/shaders/title.vtx"
#define FRG_TITLE "srcs/corewar/visu/shaders/title.frg"

static void	init_title_buffers(t_title *title)
{
	glUseProgram(title->program);
	glGenVertexArrays(1, &title->vao);
	glBindVertexArray(title->vao);
	glGenBuffers(1, &title->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, title->vbo);
	glBufferData(GL_ARRAY_BUFFER, title->mesh.nb_vtx * sizeof(t_glfloat3),
									title->mesh.coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &title->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, title->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					title->mesh.nb_triangles * sizeof(t_tri_ind),
					title->mesh.indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glUseProgram(0);
}

t_title		init_title(void)
{
	t_title		title;

	title.program = build_ogl_program(VTX_TITLE, FRG_TITLE);
	title.mesh = obj_parser(TITLE_OBJ);
	init_title_buffers(&title);
	return (title);
}
