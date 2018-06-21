/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:30:01 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:30:04 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_lfork(t_proc *proc, t_proc **begin)
{
	ft_add_proc_start(begin, ft_create_fork_proc((proc->pc + proc->arg[0][1]
		% MEM_SIZE) % MEM_SIZE, proc));
	proc->carry = 0;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
