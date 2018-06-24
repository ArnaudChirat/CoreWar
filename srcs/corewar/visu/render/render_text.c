/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:30:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/24 17:14:46 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	render_text(t_text_field *texts, t_events e)
{
	int	i;

	i = -1;
	if (e.phase == PH_GAME || e.phase == PH_FINAL)
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
