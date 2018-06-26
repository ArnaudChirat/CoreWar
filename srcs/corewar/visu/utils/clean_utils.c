/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 13:24:34 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 14:58:12 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	free_mesh(t_mesh *mesh)
{
	free_pro((void**)&mesh->coords);
	free_pro((void**)&mesh->indices);
	free_pro((void**)&mesh->indices_uni);
}

void	free_text_field(t_text_field *txt)
{
	free_mesh(&txt->mesh);
	glDeleteBuffers(1, &txt->vbo);
	glDeleteBuffers(1, &txt->ibo);
	glDeleteProgram(txt->program);
}
