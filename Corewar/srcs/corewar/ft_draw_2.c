/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 12:59:15 by clanglai          #+#    #+#             */
/*   Updated: 2018/06/08 11:29:22 by mjoubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Initialise la fenetre de ncurses ainsi que les couleurs utilises pour
**	afficher le code des joueurs.
*/

static void	ft_init_color(void)
{
	init_color(COLOR_RED, 898, 450, 450);
	init_color(COLOR_MAGENTA, 1000, 835, 309);
	init_color(COLOR_GREEN, 545, 765, 290);
	init_color(COLOR_BLUE, 11, 662, 956);
	init_color(COLOR_WHITE, 619, 619, 619);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_WHITE);
	init_pair(7, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(8, COLOR_GREEN, COLOR_WHITE);
	init_pair(9, COLOR_BLUE, COLOR_WHITE);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

t_draw		ft_init_draw(t_data data)
{
	t_draw	new;

	if (data.flag_v)
	{
		initscr();
		cbreak();
		noecho();
		keypad(stdscr, FALSE);
		start_color();
		curs_set(0);
		ft_init_color();
		getmaxyx(stdscr, new.row, new.col);
	}
	new.cyc_s = 50;
	new.cy = 1;
	new.cyc_tot = 1;
	new.ctd = CYCLE_TO_DIE;
	new.number = 1;
	new.check = 0;
	return (new);
}

/*
**	On verifie si un process se situe sur l'une des cases analysees, si oui
**	on l'affichera differement.
*/

int			ft_got_a_process(t_proc **begin, int index)
{
	t_proc *tmp;

	tmp = *begin;
	while (tmp)
	{
		if (tmp->pc == index)
			return (5);
		tmp = tmp->next;
	}
	return (0);
}

int			ft_is_champ(int i)
{
	int j;

	j = 0;
	while (j < MAX_PLAYERS)
	{
		if (j + 1 == i && g_live_tab[j].name != NULL)
			return (j + 1);
		j++;
	}
	return (j + 1);
}

/*
**	Affiche les infos de la partie : Process actifs, Cycle to die etc..
*/

void		ft_draw_general_info(t_draw draw, t_proc **begin)
{
	t_proc	*tmp;
	int		i;

	tmp = *begin;
	attroff(COLOR_PAIR(9));
	move(3 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Cycles since last check= %-4d", draw.cy);
	move(4 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Total cycles = %-4d", draw.cyc_tot);
	move(5 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Cycle to die = %-4d", draw.ctd);
	move(6 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Check = %-2d", draw.check);
	move(7 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Number = %-4d", NBR_LIVE);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	move(8 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Process = %-5d", i);
	move(9 + 64, draw.col / 2 - (64 / 2 * 3));
	printw("Max cycle per sec = %-4d", draw.cyc_s);
}
