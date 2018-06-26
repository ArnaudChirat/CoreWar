/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 12:29:56 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 23:18:55 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define TXT_CYC_VTX "srcs/corewar/visu/shaders/txt.vtx"
#define TXT_CYC_FRG "srcs/corewar/visu/shaders/txt.frg"

void			init_text(t_text_field *texts, t_mesh *alphabet,
								t_data d, char **shader_paths)
{
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	texts[TXT_CYC].program = build_ogl_program(TXT_CYC_VTX, TXT_CYC_FRG);
	texts[TXT_CYC].mesh = str_to_mesh("cycle", alphabet);
	init_text_buffers(&texts[TXT_CYC]);
	while (++i < MAX_PLAYERS)
	{
		texts[TXT_PL1 + i].program = build_ogl_program(TXT_CYC_VTX,
										shader_paths[(i + 1) * 2 + 1]);
		texts[TXT_PL1 + i].mesh = str_to_mesh(flag ?
				"fdp" : d.players_list->name, alphabet);
		init_text_buffers(&texts[TXT_PL1 + i]);
		if (!flag)
			d.players_list = d.players_list->next;
		if (d.players_list == NULL)
			flag = 1;
	}
}
