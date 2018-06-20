/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_uniforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:02 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 13:54:56 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_matrices.h"
#include "visu.h"

static void	update_main_block(t_scene s, t_matrices m)
{
	glBindBuffer(GL_UNIFORM_BUFFER, s.ublocks[UBO_MAIN].ubo);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_FINALMAT, sizeof(t_mat4), &m.final_mat);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_TIME, sizeof(float), &s.events.time);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_INTRO, sizeof(float), &s.events.intro);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void	update_raymarch_block(t_scene s, t_matrices m)
{
	glBindBuffer(GL_UNIFORM_BUFFER, s.ublocks[UBO_RM].ubo);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_RM_EYE, sizeof(t_vec3), &m.shader_eye);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void		update_uniforms(t_scene s, t_matrices m)
{
	update_main_block(s, m);
	update_raymarch_block(s, m);
}
