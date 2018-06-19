/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:52:38 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 16:52:39 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Initialisation de l'arene qui va comporter les instructions de chaque
**	programme et sur laquelle va se jouer la partie
*/

t_arena	g_arena[MEM_SIZE];

/*
**	Controle des parametres et de la validite des define dans op.h
*/

static void		ft_basic_control(int argc)
{
	int		size_magic_nbr;

	size_magic_nbr = 0;
	if (argc <= 1)
		ft_error_usage("Too few parameters\n");
	else if (argc - 1 > MAX_ARGS_NUMBER)
		ft_error_usage("Too many parameters\n");
	while (COREWAR_EXEC_MAGIC >> (size_magic_nbr * 8))
		size_magic_nbr++;
	if (size_magic_nbr > 4)
		ft_error(0, "Error: Magic number > uint_max", 0, 0);
	if (sizeof(REG_SIZE) > 4)
		ft_error(0, "Error: REG_SIZE > uint_max", 0, 0);
	if (REG_SIZE < 0)
		ft_error(0, "Error: ", 0, 0);
}

static int		ft_get_flags(char **argv, t_data *f, int argc, int i)
{
	while (i < argc && ft_is_valid_flag(argv[i]))
	{
		if (ft_strequ("-dump", argv[i]))
		{
			if (f->dump_val)
				ft_error_usage("Error : wrong flag usage");
			if (ft_isnumber(argv[i + 1]))
			{
				if ((f->dump_val = ft_atoi(argv[++i])) <= 0)
					ft_error_usage(
							"Error : You must dump memory at a valid value");
			}
			else
				ft_error_usage(
						"Error : Dump must be followed by a valid number");
		}
		if (ft_strequ("-p", argv[i]))
			f->flag_p++;
		if (ft_strequ("-v", argv[i++]))
			f->flag_v++;
		if ((f->flag_v && f->dump_val) || f->flag_v > 1 || f->flag_p > 1)
			ft_error_usage("Error : wrong flag usage");
	}
	return (i);
}

int				main(int argc, char **argv)
{
	t_data	data;
	t_draw	new;

	ft_control_define();
	ft_basic_control(argc);
	ft_bzero(&data, sizeof(t_data));
	data.end_flag = ft_get_flags(argv, &data, argc, 1);
	ft_init_func_tab();
	ft_players(&data, argv, argc);
	ft_process(&data);
	if (data.flag_p)
		ft_print_player(data.players_list);
	ft_print_game(&(data.players_list));
	new = ft_init_draw(data);
	ft_game(&data, new);
	ft_free_data(&data);
	return (0);
}
