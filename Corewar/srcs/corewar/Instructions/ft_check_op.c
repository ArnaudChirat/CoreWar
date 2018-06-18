/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:28:28 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 18:33:56 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			(*g_func_tab[OP_NBR + 1])(t_proc*, t_proc **);

t_op			g_op_tab[OP_NBR + 1] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

static void		ft_get_dir_value(t_proc *proc, int *j, int arg, int opcode)
{
	unsigned int	value;
	int				i;
	int				size;

	i = 0;
	value = 0;
	size = g_op_tab[opcode].dir_addr == 0 ? 4 : 2;
	while (i < size)
	{
		value = value * 256;
		value += g_arena[(proc->pc + *j) % MEM_SIZE].instruction & 0xff;
		(*j)++;
		i++;
	}
	proc->arg[arg][1] = value;
	(*j)--;
}

static int		ft_init_arg_type(int instru, t_proc *proc)
{
	int arg;
	int	i;

	i = 0;
	arg = g_op_tab[instru].nb_params;
	while (i < arg)
	{
		proc->arg[i][0] = g_op_tab[instru].param_type[i];
		i++;
	}
	return (arg);
}

static int		ft_is_valid_occ2(t_proc *proc, int *i, int *j, int opcode)
{
	*j = *j + 1;
	if (proc->arg[*i][0] & g_op_tab[opcode].param_type[*i])
	{
		if (proc->arg[*i][0] == T_REG)
		{
			if (ft_get_reg_value(proc, j, *i) != -1)
				;
			else
				return (-1);
		}
		else if (proc->arg[*i][0] == T_IND)
			ft_get_ind_value(proc, j, *i);
		else if (proc->arg[*i][0] == T_DIR)
			ft_get_dir_value(proc, j, *i, opcode);
		else
			return (-1);
	}
	else
		return (-1);
	*i = *i + 1;
	return (1);
}

int				ft_is_valid_occ(int opcode, char instru, t_proc *proc)
{
	int		arg;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!g_op_tab[opcode].o_cod)
		j = 0;
	else
		j = 1;
	arg = 0;
	if (!j)
		arg = ft_init_arg_type(opcode, proc);
	else if ((arg = ft_get_number_arg(instru, proc)) !=
		g_op_tab[opcode].nb_params)
		return (-1);
	while (i < arg)
	{
		if (ft_is_valid_occ2(proc, &i, &j, opcode) == -1)
			return (-1);
	}
	proc->step = j + 1;
	proc->opcode = opcode + 1;
	proc->hold = g_op_tab[opcode].nb_cycle - 1;
	return (1);
}

int				ft_check_op(t_proc *proc, int state)
{
	int i;
	int	opcode;

	i = 0;
	while (i < 4)
	{
		proc->arg[i][0] = 0;
		proc->arg[i++][1] = 0;
	}
	i = proc->pc;
	opcode = g_arena[i].instruction - 1;
	if (opcode >= OP_NBR || opcode < 0)
		return (-2);
	proc->hold = g_op_tab[opcode].nb_cycle - 1;
	if (state == 1)
	{
		if (ft_is_valid_occ(opcode, g_arena[(i + 1)
			% MEM_SIZE].instruction, proc) > 0)
			return (1);
		else
			return (-1);
	}
	return (1);
}
