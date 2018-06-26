/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_uniforms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:53:47 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 19:10:34 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static GLuint	prog_block_link(GLuint program, char *name, GLuint binding)
{
	GLuint	id;

	glUseProgram(program);
	id = glGetUniformBlockIndex(program, name);
	glUniformBlockBinding(program, id, binding);
	glUseProgram(0);
	return (id);
}

static void		attrib_raymarch_block(t_ublock *u, GLuint *programs)
{
	int	i;

	u->progs_id[PROG_BG] = prog_block_link(programs[PROG_BG],
											"raymarchBlock", UBO_RM);
	i = PROG_PLN - 1;
	while (++i <= PROG_PL4)
		u->progs_id[i] = prog_block_link(programs[i],
									"raymarchBlock", UBO_RM);
	i = PROG_TXT_PL1 - 1;
	while (++i <= PROG_TXT_PL4)
		u->progs_id[i] = prog_block_link(programs[i],
									"raymarchBlock", UBO_RM);
	glGenBuffers(1, &u->ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, u->ubo);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_RM, u->ubo);
	glBufferData(GL_UNIFORM_BUFFER, U_RM_TOT,
									NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void		attrib_main_block(t_visu v, t_ublock *u, GLuint *programs)
{
	int			i;
	t_vec2		res;

	i = -1;
	res = (t_vec2){(float)v.win_size.x, (float)v.win_size.y};
	while (++i < PROG_MAX)
		u->progs_id[i] = prog_block_link(programs[i], "mainBlock", UBO_MAIN);
	glGenBuffers(1, &u->ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, u->ubo);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_MAIN, u->ubo);
	glBufferData(GL_UNIFORM_BUFFER, U_MAIN_TOT,
									NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, U_MAIN_FINALMAT,
							sizeof(t_mat4), &v.matrices.final_mat);
	glBufferSubData(GL_UNIFORM_BUFFER, U_MAIN_RES,
							sizeof(t_vec2), &res);
	glBufferSubData(GL_UNIFORM_BUFFER, U_MAIN_RATIO,
							sizeof(float), &v.ratio);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void			init_ublocks(t_visu v, t_ublock *u)
{
	attrib_main_block(v, &u[UBO_MAIN], v.scene.all_programs);
	attrib_raymarch_block(&u[UBO_RM], v.scene.all_programs);
}
