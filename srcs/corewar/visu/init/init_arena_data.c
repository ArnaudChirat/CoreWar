/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:54:38 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/13 18:22:08 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define M_WIDTH 150
#define M_LENGTH 100

static t_vec2r	find_limits(int	size)
{
	t_vec2r	limits;
	int		i;

	i = -1;
	while (++i < size / 2)
		if (i * i >= size)
			break;
	limits = (t_vec2r){i, i};
	return (limits);
}

static void		fill_arena_coords(t_glfloat2 *coords)
{
	t_vec2r	i;
	int		ind;
	t_vec2r	limits;

	limits = find_limits(MEM_SIZE);
	i = (t_vec2r){limits.x, limits.y};
	ind = -1;
	while (--i.y >= 0)
	{
		i.x = limits.x;
		while (--i.x >= 0)
		{
			coords[++ind] =
				(t_glfloat2){(float)i.x * (float)M_WIDTH /
						(float)limits.x - (float)M_WIDTH / 2.,
							(float)i.y * (float)M_WIDTH /
						(float)limits.y - (float)M_WIDTH / 2.};
		}
	}
}

void			init_arena_data(t_v_arena *a, t_data data)
{
	int	i;

	i = -1;
	(void)data;
	while (++i < MAX_PLAYERS)
		m_pro_null(a->data_inst[i] =
				ft_memalloc(sizeof(t_glfloat2) * MEM_SIZE));
	m_pro_null(a->arena_coords = ft_memalloc(sizeof(t_glfloat2) * MEM_SIZE));
	fill_arena_coords(a->arena_coords);
}
