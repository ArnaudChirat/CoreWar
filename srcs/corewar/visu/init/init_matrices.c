/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:27:28 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 14:02:15 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_matrices.h"
#include "libft.h"

t_matrices	init_matrices(void)
{
	t_matrices	m;

	ft_bzero(&m, sizeof(t_matrices));
	m.scale = INIT_SCALE;
	m.eye = (t_vec4){INIT_XPOS, INIT_YPOS, INIT_ZPOS, 1.};
	m.tar = (t_vec4){0., 0., 0., 1.};
	m.up = (t_vec4){0., 1., 0., 0.};
	m.view_mat = look_at(m.eye, m.tar, m.up);
	m.proj_mat = persmat4new(110., 78., 1000., 1.0);
	m.final_mat = mat4xmat4(m.proj_mat, m.view_mat);
	return (m);
}
