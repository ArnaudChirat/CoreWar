/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:30:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 00:03:42 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	renderable_text(int i, int *pl_on)
{
	if (i < TXT_PL1 ||
			(i >= TXT_PL1 && i <= TXT_PL4 && pl_on[i - TXT_PL1]) ||
		(i >= TXT_PL1_PROC && i <= TXT_PL4_PROC && pl_on[i - TXT_PL1_PROC]) ||
		(i >= TXT_PL1_LIVE && i <= TXT_PL4_LIVE && pl_on[i - TXT_PL1_LIVE]) ||
		(i >= TXT_PL1_PN && i <= TXT_PL4_PN && pl_on[i - TXT_PL1_PN]) ||
		(i >= TXT_PL1_LN && i <= TXT_PL4_LN && pl_on[i - TXT_PL1_LN]))
		return (1);
	else
		return (0);
}

void		render_text(t_text_field *texts, t_text_data txt_data,
									t_events e, int *pl_on)
{
	int	i;

	i = -1;
	if (e.phase == PH_GAME || e.phase == PH_FINAL)
	{
		while (++i < TXT_MAX)
			if (renderable_text(i, pl_on))
			{
				glUseProgram(texts[i].program);
				glBindVertexArray(texts[i].vao);
				glUniform3f(texts[i].u_world_pos,
					txt_data.pos[i].x, txt_data.pos[i].y, txt_data.pos[i].z);
				glUniform1f(texts[i].u_model_rot, txt_data.rot[i]);
				glUniform1f(texts[i].u_scale, txt_data.scale[i]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texts[i].ibo);
				glDrawElements(GL_TRIANGLES, texts[i].mesh.nb_indices,
						GL_UNSIGNED_INT, NULL);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
				glUseProgram(0);
			}
	}
}
