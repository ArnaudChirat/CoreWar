/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_matrices.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:21:02 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/13 19:02:26 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_MATRICES_H
# define V_MATRICES_H

# include "libftmath.h"

# define INIT_XPOS 0.
# define INIT_YPOS 0.
# define INIT_ZPOS -60.
# define INC_POS 0.5

# define MIN_XPOS -30
# define MAX_XPOS 30

# define MIN_YPOS -30
# define MAX_YPOS 30

# define MIN_ZPOS -90
# define MAX_ZPOS -50

# define INIT_SCALE 1.0
# define INC_SCALE 0.004
# define MIN_SCALE -0.1
# define MAX_SCALE 1.4

typedef struct	s_matrices
{
	float	scale;
	float	inc_xpos;
	float	inc_ypos;
	float	inc_zpos;
	float	inc_scale;
	t_vec4	eye;
	t_vec4	tar;
	t_vec4	up;
	t_vec3	shader_eye;
	t_mat4	view_mat;
	t_mat4	proj_mat;
	t_mat4	final_mat;
}				t_matrices;

t_matrices		init_matrices(void);

#endif
