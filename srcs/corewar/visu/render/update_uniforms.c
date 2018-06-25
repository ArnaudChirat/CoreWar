/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_uniforms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:02 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 15:57:58 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_matrices.h"
#include "visu.h"

static void	update_main_block(t_scene s, t_matrices m, t_sound so)
{
	glBindBuffer(GL_UNIFORM_BUFFER, s.ublocks[UBO_MAIN].ubo);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_FINALMAT, sizeof(t_mat4), &m.final_mat);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_TIME, sizeof(float), &s.events.time);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_INTRO, sizeof(float), &s.events.intro);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_BASS, sizeof(float), &so.data.bass);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_MAIN_SPEED, sizeof(float), &m.speed);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void	update_raymarch_block(t_scene s, t_matrices m)
{
	glBindBuffer(GL_UNIFORM_BUFFER, s.ublocks[UBO_RM].ubo);
	glBufferSubData(GL_UNIFORM_BUFFER,
			U_RM_EYE, sizeof(t_vec3), &m.shader_eye);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void		update_uniforms(t_visu v)
{
	update_main_block(v.scene, v.matrices, v.sound);
	update_raymarch_block(v.scene, v.matrices);
}
