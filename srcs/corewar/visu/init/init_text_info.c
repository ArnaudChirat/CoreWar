/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:17:11 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 19:16:00 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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
		text_rotation(texts[TXT_PL1_PROC + i].mesh, i % 2 ? -55 : 55);
		text_rotation(texts[TXT_PL1_LIVE + i].mesh, i % 2 ? -55 : 55);
		init_text_buffers(&texts[TXT_PL1_PROC + i]);
		init_text_buffers(&texts[TXT_PL1_LIVE + i]);
		if (!flag)
			d.players_list = d.players_list->next;
		if (d.players_list == NULL)
			flag = 1;
	}
}
