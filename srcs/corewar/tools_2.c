/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:00:57 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 19:01:01 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Lit l'arena a partir d'un certain indice et en extrait un int
*/

int		ft_get_content_ind(t_proc *proc, int addr)
{
	int				i;
	int				res;

	i = 0;
	res = 0;
	while (i < DIR_SIZE)
	{
		if ((DIR_SIZE - i - 1) != 0)
			res += g_arena[(MEM_SIZE + (proc->pc + i + addr % MEM_SIZE)) %
			MEM_SIZE].instruction << ((DIR_SIZE - i - 1) * 8);
		else
			res += g_arena[(MEM_SIZE + (proc->pc + i + addr % MEM_SIZE)) %
				MEM_SIZE].instruction & 0xff;
		i++;
	}
	return (res);
}

int		ft_isnumber(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_isdigit(s[i]) || ((s[i] == '-' || s[i] == '+') && i == 0))
			i++;
		else
			return (0);
	}
	if (i >= 10 && ((s[0] == '-' && ft_atoi(s) > 0) || (ft_atoi(s) < 0)))
		return (0);
	return (1);
}

int		ft_is_valid_flag(char *str)
{
	if (!str)
		return (0);
	if (ft_strequ(str, "-v") || ft_strequ(str, "-dump"))
		return (1);
	if (ft_strequ(str, "-p"))
		return (1);
	return (0);
}

int		ft_get_num_player(int id)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (g_live_tab[i].id == id)
			return (i);
		i++;
	}
	return (0);
}

t_proc	*ft_reset_live_proc(t_proc **tmp)
{
	(*tmp)->live = 0;
	(*tmp)->did_live = 0;
	return (*tmp);
}
