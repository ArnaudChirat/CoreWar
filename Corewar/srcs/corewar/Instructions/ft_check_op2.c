/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_op2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:28:37 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:28:40 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void		ft_init_func_tab(void)
{
	g_func_tab[0] = &ft_live;
	g_func_tab[1] = &ft_ld;
	g_func_tab[2] = &ft_st;
	g_func_tab[3] = &ft_add;
	g_func_tab[4] = &ft_sub;
	g_func_tab[5] = &ft_and;
	g_func_tab[6] = &ft_or;
	g_func_tab[7] = &ft_xor;
	g_func_tab[8] = &ft_zjmp;
	g_func_tab[9] = &ft_ldi;
	g_func_tab[10] = &ft_sti;
	g_func_tab[11] = &ft_fork;
	g_func_tab[12] = &ft_lld;
	g_func_tab[13] = &ft_lldi;
	g_func_tab[14] = &ft_lfork;
	g_func_tab[15] = &ft_aff;
}

int			ft_get_number_arg(char instru, t_proc *proc)
{
	int arg;
	int i;

	arg = 0;
	i = 3;
	while (arg < 4)
	{
		if (instru >> 2 * i & 0x3)
		{
			proc->arg[arg][0] = instru >> 2 * i & 0x3;
			if (proc->arg[arg][0] == 3)
				proc->arg[arg][0] = T_IND;
			arg++;
		}
		else
			return (arg);
		i--;
	}
	return (arg);
}

void		ft_get_ind_value(t_proc *proc, int *j, int arg)
{
	unsigned int	value;
	int				i;

	i = 0;
	value = 0;
	while (i < 2)
	{
		value = value * 256;
		value += g_arena[(proc->pc + *j) % MEM_SIZE].instruction & 0xff;
		(*j)++;
		i++;
	}
	proc->arg[arg][1] = value;
	(*j)--;
}

int			ft_get_reg_value(t_proc *proc, int *j, int arg)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	while (i < 1)
	{
		value = value * 256;
		value += g_arena[(proc->pc + *j) % MEM_SIZE].instruction & 0xff;
		i++;
		(*j)++;
	}
	if (value > REG_NUMBER || value <= 0)
		return (-1);
	proc->arg[arg][1] = value - 1;
	(*j)--;
	return (1);
}
