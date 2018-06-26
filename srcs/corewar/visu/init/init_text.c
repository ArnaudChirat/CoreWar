/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:29:56 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 17:08:01 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define TXT_CYC_POS (t_glfloat3){6, -115, 0.0}
#define TXT_CYC_VTX "srcs/corewar/visu/shaders/txt.vtx"
#define TXT_CYC_FRG "srcs/corewar/visu/shaders/txt.frg"

static void		init_buffers(t_text_field *text, t_glfloat3 pos)
{
	glUseProgram(text->program);
	glGenVertexArrays(1, &text->vao);
	glBindVertexArray(text->vao);
	glGenBuffers(1, &text->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, text->vbo);
	glBufferData(GL_ARRAY_BUFFER, text->mesh.nb_vtx * sizeof(t_glfloat3),
									text->mesh.coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &text->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					text->mesh.nb_indices * sizeof(GLuint),
					text->mesh.indices, GL_STATIC_DRAW);
	text->u_world_pos =
		glGetUniformLocation(text->program, "world_pos");
	glUniform3f(text->u_world_pos, pos.x, pos.y, pos.z);
	glBindVertexArray(0);
	glUseProgram(0);
}

static void		fill_name_pos(t_glfloat3 *pos)
{
	pos[0] = (t_glfloat3){154., 45, -25.5};
	pos[1] = (t_glfloat3){-124., 45, -15.5};
	pos[2] = (t_glfloat3){154., -45, -25.5};
	pos[3] = (t_glfloat3){-124., -45, -15.5};
}

static void		text_rotation(t_mesh text, float angle)
{
	int		i;
	t_vec3	tmp;

	i = -1;
	while (++i < text.nb_vtx)
	{
		tmp = mat4xvec4_tovec3(rotymat4new(angle),
						(t_vec4){text.coords[i].x,
						text.coords[i].y, text.coords[i].z, 1.0});
		text.coords[i] = (t_glfloat3){tmp.x, tmp.y, tmp.z};
	}
}

void			init_text(t_text_field *texts, t_mesh *alphabet,
								t_data d, char **shader_paths)
{
	int			i;
	int			flag;
	t_glfloat3	name_pos[MAX_PLAYERS];

	i = -1;
	flag = 0;
	fill_name_pos(name_pos);
	texts[TXT_CYC].program = build_ogl_program(TXT_CYC_VTX, TXT_CYC_FRG);
	texts[TXT_CYC].mesh = str_to_mesh("cycle", alphabet);
	init_buffers(&texts[TXT_CYC], TXT_CYC_POS);
	while (++i < MAX_PLAYERS)
	{
		texts[TXT_PL1 + i].program = build_ogl_program(TXT_CYC_VTX,
										shader_paths[(i + 1) * 2 + 1]);
		texts[TXT_PL1 + i].mesh = str_to_mesh(flag ? "" : d.players_list->name,
											alphabet);
		text_rotation(texts[TXT_PL1 + i].mesh, i % 2 ? -55 : 55);
		init_buffers(&texts[TXT_PL1 + i], name_pos[i]);
		if (!flag)
			d.players_list = d.players_list->next;
		if (d.players_list == NULL)
			flag = 1;
	}
}
