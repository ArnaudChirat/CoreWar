/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:47:27 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 16:51:30 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void		ft_create_player(t_player **new, unsigned int *size_read,
		char *line, char *file_name)
{
	char	*tmp;

	(void)size_read;
	tmp = ft_cut_read(line, 0, MAGIC_LENGTH);
	(*new)->magic_nbr = ft_convert_int_base(tmp);
	if ((*new)->magic_nbr != COREWAR_EXEC_MAGIC)
		ft_error(0, "Error: Champion magic number is wrong", 0, 0);
	(*new)->name = ft_cut_read(line, MAGIC_LENGTH, PROG_NAME_LENGTH);
	tmp = ft_cut_read(line, MAGIC_LENGTH + PROG_NAME_LENGTH + 4, SIZE_LENGTH);
	(*new)->size_prog = ft_convert_int_base(tmp);
	(*new)->comment = ft_cut_read(line, HEADER_MAX_SIZE + 8 -
			(COMMENT_LENGTH + 4), COMMENT_LENGTH);
	if (!((*new)->prog = ft_memalloc((*new)->size_prog)))
		ft_error(0, "Malloc failed in ft_create_player", 0, 0);
	if ((*new)->size_prog == 0)
		ft_error(3, file_name, 0, 0);
	if (HEADER_MAX_SIZE + 8 + (*new)->size_prog != *size_read)
		ft_error(6, file_name, 0, 0);
	if (!ft_memcpy((*new)->prog, line + HEADER_MAX_SIZE + 8, (*new)->size_prog))
		ft_error(0, "Malloc failed in ft_create_player", 0, 0);
	(*new)->next = NULL;
	ft_strdel(&line);
}

void		ft_add_players(t_data *data, t_player **new)
{
	t_player	*players_list;

	players_list = data->players_list;
	if (!data->players_list)
		data->players_list = (*new);
	else
	{
		while (players_list->next)
			players_list = players_list->next;
		players_list->next = (*new);
	}
}

void		ft_launch_players(t_player *players_list, int player_nbr, int ind_p)
{
	unsigned int		index_prog;
	int					arena_player;

	arena_player = MEM_SIZE / player_nbr;
	while (players_list)
	{
		index_prog = 0;
		if (players_list->pc == -1)
		{
			ind_p = (players_list->player_nbr - 1) * arena_player;
			players_list->pc = ind_p;
		}
		else
			ind_p = players_list->pc;
		while (index_prog < players_list->size_prog)
		{
			if (g_arena[ind_p % MEM_SIZE].player != 0)
				ft_error_usage("Error: Two champions overlap");
			g_arena[ind_p % MEM_SIZE].player = players_list->player_nbr;
			g_arena[ind_p++ % MEM_SIZE].instruction =
				players_list->prog[index_prog++ % MEM_SIZE];
		}
		players_list = players_list->next;
	}
}

void		ft_champion(t_data *data, t_player **new, char *file_name, int fd)
{
	char			*line;
	static int		player_nbr = 1;
	unsigned int	size_read;

	size_read = 0;
	if (!*new)
	{
		if (!((*new) = (t_player*)malloc(sizeof(t_player))))
			ft_error(0, "Malloc failed in ft_champion (t_player *new)", 0, 0);
		ft_bzero(*new, sizeof(**new));
		(*new)->pc = -1;
	}
	(*new)->player_nbr = player_nbr;
	player_nbr++;
	line = ft_read_champion(fd, &size_read, file_name);
	ft_control_line(line, file_name);
	ft_create_player(new, &size_read, line, file_name);
	ft_add_players(data, new);
}

void		ft_flags(int *index, char **argv, t_player **new)
{
	if (!*new)
	{
		if (!((*new) = (t_player*)malloc(sizeof(t_player))))
			ft_error(0, "Malloc failed in ft_flags(t_player *new)", 0, 0);
		ft_bzero(*new, sizeof(**new));
		(*new)->pc = -1;
	}
	if (argv[*index][1] == 'n')
		if (ft_isnumber(argv[*index + 1]) != 0 &&
				ft_atoi(argv[*index + 1]) != 0)
			((*new)->id = ft_atoi(argv[*index + 1]));
		else
			ft_error_usage("Error Wrong flag value for -n");
	else if (argv[*index][1] == 'a')
	{
		if (ft_isnumber(argv[*index + 1]) == 0)
			ft_error_usage("Error: Wrong flag value for address");
		(*new)->pc = (MEM_SIZE + (ft_atoi(argv[*index + 1]) % MEM_SIZE))
			% MEM_SIZE;
	}
	else
		ft_error_usage("Error: Wrong flag");
	if (argv[*index + 2] == 0)
		ft_error_usage("Error: Invalid input");
	*index += 2;
}
