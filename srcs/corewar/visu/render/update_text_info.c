/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_text_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 00:12:50 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 02:36:07 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define EST_SIZE_VTX (1800 * 5)
#define EST_SIZE_IND (1800 * 5 * 3)

static void	update_info(int *nb_process, int *nb_lives, t_proc *procs)
{
	int	i;

	ft_bzero(nb_process, sizeof(int) * MAX_PLAYERS);
	ft_bzero(nb_lives, sizeof(int) * MAX_PLAYERS);
	while (procs)
	{
		nb_process[procs->num - 1]++;
		procs = procs->next;
	}
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		nb_lives[i] = g_live_tab[i].live;
	}
}

static void	refresh_str_mesh(int *nb_process, int *nb_lives,
									t_text_field *txt, t_mesh *alphabet)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		str = ft_itoa(nb_process[i]);
		free_mesh(&txt[TXT_PL1_PN + i].mesh);
		txt[TXT_PL1_PN + i].mesh = str_to_mesh(str, alphabet);
		free_pro((void**)&str);
	}
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		str = ft_itoa(nb_lives[i]);
		free_mesh(&txt[TXT_PL1_LN + i].mesh);
		txt[TXT_PL1_LN + i].mesh = str_to_mesh(str, alphabet);
		free_pro((void**)&str);
	}
}

static void	update_buffers(t_text_field *text)
{
	glBindBuffer(GL_ARRAY_BUFFER, text->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
			EST_SIZE_VTX * sizeof(t_glfloat3), text->mesh.coords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text->ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
			EST_SIZE_IND * sizeof(GLuint), text->mesh.indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void	update_text_info(t_scene *scene, t_data *d)
{
	int	i;

	update_info(scene->nb_process, scene->nb_lives, d->proc_list);
	refresh_str_mesh(scene->nb_process, scene->nb_lives,
								scene->texts, scene->alphabet_3d);
	i = -1;
	while (++i < MAX_PLAYERS)
		update_buffers(&scene->texts[TXT_PL1_PN + i]);
	i = -1;
	while (++i < MAX_PLAYERS)
		update_buffers(&scene->texts[TXT_PL1_LN + i]);
}
