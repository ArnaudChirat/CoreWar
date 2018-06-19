/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_model.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:10 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/12 15:39:44 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define MOD_NB_VTX 4
#define MOD_NB_IND 4

static t_glfloat3	*gen_coords(void)
{
	t_glfloat3	*coords;

	m_pro_null(coords = ft_memalloc(sizeof(t_glfloat3) * MOD_NB_VTX));
	coords[0] = (t_glfloat3) {-1.0, -1.0, 0.0};
	coords[1] = (t_glfloat3) {1.0, -1.0, 0.0};
	coords[2] = (t_glfloat3) {1.0, 1.0, 0.0};
	coords[3] = (t_glfloat3) {-1.0, 1.0, 0.0};
	return (coords);
}

static GLuint		*gen_indices(void)
{
	GLuint	*indices;

	m_pro_null(indices = ft_memalloc(sizeof(GLuint) * MOD_NB_IND));
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	return (indices);
}

t_mesh				create_arena_mesh(void)
{
	t_mesh	model;

	ft_bzero(&model, sizeof(t_mesh));
	model.coords = gen_coords();
	model.nb_vtx = MOD_NB_VTX;
	model.indices_uni = gen_indices();
	model.nb_indices = MOD_NB_IND;
	return (model);
}
