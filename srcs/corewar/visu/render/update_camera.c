/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:25:19 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 15:29:09 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		update_camera(t_matrices *mat)
{
	//mat->scal = clamp(mat->scal + mat->inc_scal, MIN_SCALE, MAX_SCALE);
	mat->eye.x = clamp(mat->eye.x + mat->inc_xpos, MIN_XPOS, MAX_XPOS);
	mat->eye.y = clamp(mat->eye.y + mat->inc_ypos, MIN_YPOS, MAX_YPOS);
	mat->eye.z = clamp(mat->eye.z + mat->inc_zpos, MIN_ZPOS, MAX_ZPOS);
	mat->eye.w = 1.;
	mat->shader_eye = (t_vec3){mat->eye.x, mat->eye.y, mat->eye.z / 10.};
	mat->view_mat = look_at(mat->eye, mat->tar, mat->up);
	mat->final_mat = mat4xmat4(mat4inv(mat->proj_mat), mat->view_mat);
}