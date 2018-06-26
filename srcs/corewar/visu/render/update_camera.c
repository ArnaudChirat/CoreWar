/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:25:19 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 16:02:08 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		update_camera(t_matrices *mat)
{
	mat->eye.x = clamp(mat->eye.x + mat->inc_xpos, MIN_XPOS, MAX_XPOS);
	mat->eye.y = clamp(mat->eye.y + mat->inc_ypos, MIN_YPOS, MAX_YPOS);
	mat->eye.w = 1.;
	mat->shader_eye = (t_vec3){mat->eye.x / 100., mat->eye.y / 100.,
						mat->shader_eye.z + mat->speed};
	mat->view_mat = look_at(mat->eye, mat->tar, mat->up);
	mat->final_mat = mat4xmat4(mat4inv(mat->proj_mat), mat->view_mat);
}
