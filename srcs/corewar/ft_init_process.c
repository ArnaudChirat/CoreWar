/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:49:41 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/27 01:10:54 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Fonction de creation des processus initiaux et donc vierge d'information
**	l'adresse est determinee selon le numero du joueur
*/

t_proc		*ft_create_init_proc(int addr, int player, int index)
{
	t_proc	*new;
	int		i;

	i = 1;
	if (!(new = malloc(sizeof(t_proc))))
		exit(0);
	new->reg[0] = -player;
	while (i < REG_NUMBER)
		new->reg[i++] = 0;
	new->next = NULL;
	new->pc = addr;
	new->carry = 0;
	new->index = 0;
	new->hold = 0;
	new->step = 0;
	new->live = 0;
	new->num = index;
	new->did_live = 0;
	return (new);
}

/*
**	Fonction de creation d'un processus apres un fork, le nouveau processus
**	herite des caracteristiques de son parent : registres et carry
*/

t_proc		*ft_create_fork_proc(int addr, t_proc *parent)
{
	t_proc	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(t_proc))))
		exit(0);
	while (i < REG_NUMBER)
	{
		new->reg[i] = parent->reg[i];
		i++;
	}
	new->next = NULL;
	new->pc = addr;
	new->carry = parent->carry;
	new->index = 0;
	new->hold = 0;
	new->opcode = 0;
	new->live = 0;
	new->num = parent->num;
	new->did_live = parent->did_live;
	return (new);
}

/*
**	Ajout d'un processus a la fin de la liste des processus
*/

void		ft_add_proc_end(t_proc **begin, t_proc *elem)
{
	t_proc	*tmp;
	int		i;

	i = 1;
	if (!(*begin))
		*begin = elem;
	else
	{
		tmp = *begin;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		tmp->next = elem;
		tmp->next->index = i;
	}
}

/*
**	Ajout d'un processus au debut de la liste des processus. C'est cette
**	fonction qui est utilises pour realiser des forks au cours de la partie
*/

void		ft_add_proc_start(t_proc **begin, t_proc *elem)
{
	if (*begin == NULL)
		*begin = elem;
	else
	{
		elem->next = *begin;
		*begin = elem;
	}
}
