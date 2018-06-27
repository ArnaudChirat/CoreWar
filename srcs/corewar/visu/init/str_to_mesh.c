/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:52:44 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 01:55:33 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define X_OFFSET -0.5

static int		get_alphabet_index(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a');
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	else if (c >= '0' && c <= '9')
		return (c - '0' + A_NUM);
	else if (c == '_')
		return (A_UNDERSCORE);
	return ('a');
}

static void		add_letter_to_str(t_mesh *str, t_mesh letter, int pos)
{
	int	i;

	m_pro_null(str->indices = realloc(str->indices, sizeof(GLuint) *
				(str->nb_indices + letter.nb_indices)));
	m_pro_null(str->coords = realloc(str->coords, sizeof(t_glfloat3) *
				(str->nb_vtx + letter.nb_vtx)));
	i = str->nb_indices - 1;
	while (++i < str->nb_indices + letter.nb_indices)
		((GLuint*)str->indices)[i] =
			((GLuint*)letter.indices)[i - str->nb_indices] + str->nb_vtx;
	i = str->nb_vtx - 1;
	while (++i < str->nb_vtx + letter.nb_vtx)
	{
		str->coords[i] = (t_glfloat3)
				{letter.coords[i - str->nb_vtx].x + pos * X_OFFSET,
				letter.coords[i - str->nb_vtx].y,
				letter.coords[i - str->nb_vtx].z};
	}
	str->nb_indices += letter.nb_indices;
	str->nb_vtx += letter.nb_vtx;
}

t_mesh			str_to_mesh(const char *str, t_mesh *alphabet)
{
	int		i;
	t_mesh	mesh;

	i = -1;
	ft_bzero(&mesh, sizeof(t_mesh));
	while (str[++i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			add_letter_to_str(&mesh,
					alphabet[get_alphabet_index(str[i])], i);
	}
	return (mesh);
}
