/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_define.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:52:49 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/26 16:52:55 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Controle des DEFINE contenu dans le op.h et definissant les regles du jeu
*/

void		ft_control_define(void)
{
	if (IND_SIZE <= 0 || REG_SIZE <= 0 || MAX_PLAYERS <= 0 || MAX_PLAYERS > 4
		|| MEM_SIZE <= 23 || REG_CODE <= 0 || DIR_CODE <= 0 || IND_CODE <= 0
		|| MAX_ARGS_NUMBER <= 0 || IDX_MOD <= 0
		|| CHAMP_MAX_SIZE <= 0 || REG_NUMBER <= 1 || CYCLE_TO_DIE <= 0
		|| NBR_LIVE <= 0 || MAX_CHECKS <= 0 || OP_NBR <= 0 || T_REG <= 0
		|| T_DIR <= 0 || T_IND <= 0 || T_LAB <= 0)
	{
		ft_putstr_fd("Wrong define in op.h", 2);
		exit(1);
	}
}
