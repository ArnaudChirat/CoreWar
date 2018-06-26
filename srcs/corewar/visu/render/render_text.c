/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:30:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 19:26:10 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	render_text(t_text_field *texts, t_glfloat3 *u_pos,
									t_events e, int *pl_on)
{
	int	i;

	i = -1;
	if (e.phase == PH_GAME || e.phase == PH_FINAL)
	{
		while (++i < TXT_MAX)
			if (i < TXT_PL1 ||
			(i >= TXT_PL1 && i <= TXT_PL4 && pl_on[i - TXT_PL1]) ||
		(i >= TXT_PL1_PROC && i <= TXT_PL4_PROC && pl_on[i - TXT_PL1_PROC]) ||
		(i >= TXT_PL1_LIVE && i <= TXT_PL4_LIVE && pl_on[i - TXT_PL1_LIVE]))
			{
				glUseProgram(texts[i].program);
				glBindVertexArray(texts[i].vao);
				glUniform3f(texts[i].u_world_pos,
						u_pos[i].x, u_pos[i].y, u_pos[i].z);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texts[i].ibo);
				glDrawElements(GL_TRIANGLES, texts[i].mesh.nb_indices,
						GL_UNSIGNED_INT, NULL);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				glUseProgram(0);
			}
	}
}
