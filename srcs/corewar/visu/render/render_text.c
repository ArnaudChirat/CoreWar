/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:30:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 15:10:08 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	render_text(t_text_field *texts)
{
	int	i;

	i = -1;
	while (++i < TXT_MAX)
	{
		glUseProgram(texts[i].program);
		glBindVertexArray(texts[i].vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texts[i].ibo);
		glDrawElements(GL_TRIANGLES, texts[i].mesh.nb_indices,
									GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}
