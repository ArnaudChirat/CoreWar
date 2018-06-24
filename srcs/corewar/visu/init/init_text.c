/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:29:56 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 15:17:16 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define X_OFFSET -0.5

#define TXT_CYC_POS (t_glfloat3){1.3, -14.8, 0.0}
#define TXT_CYC_VTX "srcs/corewar/visu/shaders/txt.vtx"
#define TXT_CYC_FRG "srcs/corewar/visu/shaders/txt.frg"

static int		get_alphabet_index(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a');
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	else if (c >= '0' && c <= '9')
		return (c - '0' + A_NUM);
	else if (c == '_')
		return (A_UNDERSCORE);
	return ('a');
}

static void		add_letter_to_str(t_mesh *str, t_mesh letter, t_glfloat3 world,
																	int pos)
{
	int	i;

	m_pro_null(str->indices = realloc(str->indices, sizeof(GLuint) * 
				(str->nb_indices + letter.nb_indices)));
	m_pro_null(str->coords = realloc(str->coords, sizeof(t_glfloat3) * 
				(str->nb_vtx + letter.nb_vtx)));
	i = str->nb_indices - 1;
	while (++i < str->nb_indices + letter.nb_indices)
		((GLuint*)str->indices)[i] =
			((GLuint*)letter.indices)[i - str->nb_indices] + str->nb_vtx;
	i = str->nb_vtx - 1;
	while (++i < str->nb_vtx + letter.nb_vtx)
	{
		str->coords[i] = (t_glfloat3)
				{letter.coords[i - str->nb_vtx].x + world.x + pos * X_OFFSET,
				letter.coords[i - str->nb_vtx].y + world.y,
				letter.coords[i - str->nb_vtx].z + world.z};
	}
	str->nb_indices += letter.nb_indices;
	str->nb_vtx += letter.nb_vtx;
}

static t_mesh	str_to_mesh(const char *str, t_mesh *alphabet, t_glfloat3 pos)
{
	int		i;
	t_mesh	mesh;

	i = -1;
	ft_bzero(&mesh, sizeof(t_mesh));
	while (str[++i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			add_letter_to_str(&mesh,
					alphabet[get_alphabet_index(str[i])], pos, i);
	}
	printf("%d\n", mesh.nb_vtx);
	return (mesh);
}

static void		init_buffers(t_text_field *text)
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
	glBindVertexArray(0);
	glUseProgram(0);

}

void			init_text(t_text_field *texts, t_mesh *alphabet, t_data d)
{
	(void)d;
	texts[TXT_CYC].program = build_ogl_program(TXT_CYC_VTX, TXT_CYC_FRG);
	texts[TXT_CYC].mesh = str_to_mesh("cycle", alphabet, TXT_CYC_POS);
	init_buffers(&texts[TXT_CYC]);
}
