/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_text_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 00:12:50 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 17:00:37 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define EST_SIZE_VTX (1800 * 6)
#define EST_SIZE_IND (1800 * 6 * 3)
#define MAX_INT_VALUE 99999
#define MAX_STRING "99999"

static void	update_info(unsigned int *nb_process, unsigned int *nb_lives,
						t_proc *procs)
{
	int	i;

	ft_bzero(nb_process, sizeof(unsigned int) * MAX_PLAYERS);
	ft_bzero(nb_lives, sizeof(unsigned int) * MAX_PLAYERS);
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

static void	refresh_str_mesh(unsigned int *nb_process, unsigned int *nb_lives,
									t_text_field *txt, t_mesh *alphabet)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		str = ft_itoa(nb_process[i]);
		free_mesh(&txt[TXT_PL1_PN + i].mesh);
		txt[TXT_PL1_PN + i].mesh =
			str_to_mesh((nb_process[i] >= MAX_INT_VALUE ?
										MAX_STRING : str), alphabet);
		free_pro((void**)&str);
	}
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		str = ft_itoa(nb_lives[i]);
		free_mesh(&txt[TXT_PL1_LN + i].mesh);
		txt[TXT_PL1_LN + i].mesh =
			str_to_mesh((nb_lives[i] >= MAX_INT_VALUE ?
										MAX_STRING : str), alphabet);
		free_pro((void**)&str);
	}
}

static void	update_buffers(t_text_field *text)
{
	glBindBuffer(GL_ARRAY_BUFFER, text->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
			sizeof(t_glfloat3) * EST_SIZE_VTX, text->mesh.coords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text->ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
			sizeof(GLuint) * EST_SIZE_IND, text->mesh.indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void		update_text_info(t_scene *scene, t_data *d)
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
