/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:23:59 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 16:33:29 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define EST_SIZE_VTX (1800 * 6)
#define EST_SIZE_IND (1800 * 6 * 3)

void		init_text_buffers_empty(t_text_field *text)
{
	glUseProgram(text->program);
	glGenVertexArrays(1, &text->vao);
	glBindVertexArray(text->vao);
	glGenBuffers(1, &text->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, text->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_glfloat3) * EST_SIZE_VTX,
									NULL, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &text->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					sizeof(GLuint) * EST_SIZE_IND,
					NULL, GL_STREAM_DRAW);
	text->u_world_pos =
		glGetUniformLocation(text->program, "world_pos");
	text->u_model_rot =
		glGetUniformLocation(text->program, "model_rot");
	text->u_scale =
		glGetUniformLocation(text->program, "scale");
	glBindVertexArray(0);
	glUseProgram(0);
}

void		init_text_buffers(t_text_field *text)
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
	text->u_model_rot =
		glGetUniformLocation(text->program, "model_rot");
	text->u_scale =
		glGetUniformLocation(text->program, "scale");
	glBindVertexArray(0);
	glUseProgram(0);
}

void		text_rotation(t_mesh text, float angle)
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
