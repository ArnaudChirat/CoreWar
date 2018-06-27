/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_struc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:40:58 by achirat           #+#    #+#             */
/*   Updated: 2018/06/27 09:38:25 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUC_H
# define VM_STRUC_H

# include "vm.h"
# include <pthread.h>
# define FAILED_INSTRUC		-1
# define INSTRUCT_IN_CYCLE	0
# define INSTRUCT_END 		1

extern t_op				g_op_tab[OP_NBR + 1];

/*
** Structure containing the information of each point of the arena
*/

typedef struct			s_arena
{
	char	player;
	char	instruction;
}						t_arena;

extern t_arena			g_arena[MEM_SIZE];

/*
** Structure containing the information of each processus
*/

typedef struct			s_proc
{
	unsigned int	reg[REG_NUMBER];
	int				pc;
	int				carry;
	int				index;
	int				live;
	unsigned int	arg[4][2];
	int				hold;
	int				step;
	int				opcode;
	int				did_live;
	int				num;
	struct s_proc	*next;
}						t_proc;

/*
** Structure containing champ names, numbers + live counters
*/

typedef struct			s_live
{
	int				id;
	int				player_nbr;
	char			*name;
	int				live;
	int				last;
}						t_live;

extern t_live			g_live_tab[MAX_PLAYERS];

/*
** Structure containing the information of each player
*/

typedef struct			s_player
{
	int				id;
	int				player_nbr;
	int				pc;
	unsigned int	magic_nbr;
	char			*name;
	char			*comment;
	unsigned int	size_prog;
	char			*prog;
	struct s_player	*next;
}						t_player;

/*
** Structure containing all the information of the game
*/

typedef struct			s_data
{
	int				increm;
	int				nbr_player;
	int				dump_val;
	int				flag_v;
	int				live;
	int				end_flag;
	int				flag_p;
	t_proc			*proc_list;
	t_player		*players_list;
	int				cyc_since_refresh;
	int				ctd;
	int				cyc_tot;
	int				cy;
	int				check;
	int				number;
}						t_data;

#endif
