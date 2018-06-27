/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:17:11 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 02:25:04 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void			init_text_info_nb(t_text_field *texts, GLuint program)
{
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	while (++i < MAX_PLAYERS)
	{
		texts[TXT_PL1_PN + i].program = program;
		texts[TXT_PL1_LN + i].program = program;
		ft_bzero(&texts[TXT_PL1_PN + i].mesh, sizeof(t_mesh));
		ft_bzero(&texts[TXT_PL1_LN + i].mesh, sizeof(t_mesh));
		init_text_buffers_empty(&texts[TXT_PL1_PN + i]);
		init_text_buffers_empty(&texts[TXT_PL1_LN + i]);
	}
}

void			init_text_info(t_text_field *texts, t_mesh *alphabet,
								t_data d, GLuint program)
{
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	while (++i < MAX_PLAYERS)
	{
		texts[TXT_PL1_PROC + i].program = program;
		texts[TXT_PL1_PROC + i].mesh = str_to_mesh("proc", alphabet);
		texts[TXT_PL1_LIVE + i].program = program;
		texts[TXT_PL1_LIVE + i].mesh = str_to_mesh("live", alphabet);
		init_text_buffers(&texts[TXT_PL1_PROC + i]);
		init_text_buffers(&texts[TXT_PL1_LIVE + i]);
		if (!flag)
			d.players_list = d.players_list->next;
		if (d.players_list == NULL)
			flag = 1;
	}
}
