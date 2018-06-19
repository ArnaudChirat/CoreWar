/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:50:17 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 15:23:02 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Affiche les infos des joueurs en fonction de leur position : nom, couleur
**	nombre de lives
*/

void	ft_draw_joueurs(t_draw draw, t_proc **begin)
{
	int	i;

	i = 1;
	while (i - 1 < MAX_PLAYERS)
	{
		attron(COLOR_PAIR(5));
		if (g_live_tab[i - 1].name)
		{
			move(i < 3 ? 2 : 2 + 32, i % 2 == 1 ? 2 :
					(draw.col - (64 * 3)) / 2 + 64 * 3 + 2);
			printw("Player %d :", g_live_tab[i - 1].id);
			move(i < 3 ? 3 : 2 + 33, i % 2 == 1 ? 2 :
					(draw.col - (64 * 3)) / 2 + 64 * 3 + 2);
			printw("Name = ");
			attron(COLOR_PAIR(ft_is_champ(g_live_tab[i - 1].id)));
			printw("%s\n", g_live_tab[i - 1].name);
			attroff(COLOR_PAIR(ft_is_champ(g_live_tab[i - 1].id)));
			move(i < 3 ? 4 : 2 + 34, i % 2 == 1 ? 2 :
					(draw.col - (64 * 3)) / 2 + 64 * 3 + 2);
			printw("Live since cycle started = %d\n", g_live_tab[i - 1].live);
		}
		i++;
	}
	ft_draw_general_info(draw, begin);
}

void	ft_redimension(t_draw *draw)
{
	int old_row;
	int old_col;

	old_row = draw->row;
	old_col = draw->col;
	getmaxyx(stdscr, draw->row, draw->col);
	if (old_row != draw->row || old_col != draw->col)
		erase();
}

/*
**	Gere l'acceleration, la deceleration du rythme de la partie
*/

void	ft_handle_cycle_speed(t_draw *draw, t_proc **begin, char ch)
{
	int	tmp;

	tmp = 0;
	if ((ch == 'q' || ch == 'w') && draw->cyc_s > 1)
	{
		tmp = ch == 'q' ? -10 : -1;
		draw->cyc_s = draw->cyc_s + tmp < 1 ? 1 : draw->cyc_s + tmp;
	}
	if ((ch == 'e' || ch == 'r') && draw->cyc_s < 1000)
	{
		tmp = ch == 'r' ? 10 : 1;
		draw->cyc_s = draw->cyc_s + tmp > 1000 ? 1000 : draw->cyc_s + tmp;
	}
	if (draw->col >= 64 * 3 + 50)
		ft_draw_general_info(*draw, begin);
}

/*
**	Gere l'activation des commandes a la disposition de l'utilisateur
*/

void	ft_handle_key_input(t_draw *draw, t_proc **begin)
{
	char	ch;
	int		tmp;

	ch = '\0';
	timeout(1000 / draw->cyc_s);
	ch = getch();
	tmp = 0;
	ft_handle_cycle_speed(draw, begin, ch);
	if (ch == ' ' || draw->cyc_tot == 1)
		while ((ch = getch()) != ' ')
			ft_handle_cycle_speed(draw, begin, ch);
}

/*
**	La fonction d'affichage principale, appelle a chaque cycle
*/

void	ft_draw_cycle(t_draw *draw, t_data *data)
{
	int		i;
	int		j;

	ft_redimension(draw);
	if (draw->col >= 64 * 3 + 50)
		ft_draw_joueurs(*draw, &data->proc_list);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			move(i / 64 + 2, draw->col / 2 - (64 / 2) * 3);
		j = g_arena[i].player == 0 ? 5 : g_arena[i].player;
		attron(COLOR_PAIR(j + ft_got_a_process(&data->proc_list, i)));
		printw("%2.2hhx ", g_arena[i++].instruction);
	}
	if (draw->col >= 64 * 3 + 50)
		ft_draw_general_info(*draw, &data->proc_list);
	if (data->dump_val && draw->cyc_tot == data->dump_val)
	{
		getch();
		endwin();
	}
	ft_handle_key_input(draw, &data->proc_list);
	refresh();
}
