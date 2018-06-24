/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_model.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:28:10 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 16:08:30 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define MOD_NB_VTX 8
#define MOD_NB_TRI 12
#define MOD_NB_IND MOD_NB_TRI * 3

static t_glfloat3	*gen_coords(void)
{
	t_glfloat3	*coords;

	m_pro_null(coords = ft_memalloc(sizeof(t_glfloat3) * MOD_NB_VTX));
	coords[0] = (t_glfloat3) {CT_WIDTH, 0.0, 0.0};
	coords[1] = (t_glfloat3) {CT_WIDTH, 0.0, -1.0};
	coords[2] = (t_glfloat3) {CT_WIDTH, 1.0, -1.0};
	coords[3] = (t_glfloat3) {CT_WIDTH, 1.0, 0.0};
	coords[4] = (t_glfloat3) {0.0, 0.0, 0.0};
	coords[5] = (t_glfloat3) {0.0, 1.0, 0.};
	coords[6] = (t_glfloat3) {0.0, 1.0, -1.0};
	coords[7] = (t_glfloat3) {0.0, 0.0, -1.0};
	return (coords);
}

static t_tri_ind	*gen_indices(void)
{
	t_tri_ind	*indices;

	m_pro_null(indices = ft_memalloc(sizeof(t_tri_ind) * MOD_NB_TRI));
	indices[0] = (t_tri_ind){0, 1, 2};
	indices[1] = (t_tri_ind){2, 3, 0};
	indices[2] = (t_tri_ind){3, 2, 6};
	indices[3] = (t_tri_ind){6, 5, 3};
	indices[4] = (t_tri_ind){7, 4, 5};
	indices[5] = (t_tri_ind){5, 6, 7};
	indices[6] = (t_tri_ind){4, 0, 3};
	indices[7] = (t_tri_ind){3, 5, 4};
	indices[8] = (t_tri_ind){1, 7, 6};
	indices[9] = (t_tri_ind){6, 2, 1};
	indices[10] = (t_tri_ind){0, 4, 7};
	indices[11] = (t_tri_ind){7, 1, 0};
	return (indices);
}

t_mesh				create_counter_mesh(void)
{
	t_mesh	model;

	ft_bzero(&model, sizeof(t_mesh));
	model.coords = gen_coords();
	model.nb_vtx = MOD_NB_VTX;
	model.indices = gen_indices();
	model.nb_indices = MOD_NB_IND;
	model.nb_triangles = MOD_NB_TRI;
	return (model);
}
