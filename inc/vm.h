/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:58:18 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 11:31:06 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "vm_struc.h"
# include "errno.h"
# include "libft.h"
# include <time.h>
# include <ncurses.h>

typedef struct s_visu t_visu;

extern void		(*g_func_tab[OP_NBR + 1])(t_proc*, t_proc **);

void			ft_free_data(t_data *data);
void			ft_control_define(void);
/*
** Functions in TOOLS.C && TOOLS_2.c
*/
void			ft_error(int error_code, char *msg, int value1, int value2);
void			ft_error_usage(char *msg);
char			*ft_cut_read(char *s, int start, int len);
unsigned int	ft_convert_int_base(char *str);
int				ft_get_content_ind(t_proc *proc, int j);
int				ft_isnumber(char *s);
int				ft_is_valid_flag(char *str);
t_proc			*ft_reset_live_proc(t_proc **tmp);
/*
** Functions in FT_INIT_PROCESS.C
*/
t_proc			*ft_create_init_proc(int addr, int player, int index);
t_proc			*ft_create_fork_proc(int addr, t_proc *parent);
void			ft_add_proc(t_proc **begin, t_proc *elem);
void			ft_add_proc_start(t_proc **begin, t_proc *elem);
/*
** Functions in FT_PLAYERS & FT_PLAYERS_2 >C
*/
void			ft_players(t_data *data, char **argv, int argc);
void			ft_launch_players(t_player *p_list, int p_nbr,
				int index_player);
void			ft_add_players(t_data *data, t_player **new_player);
void			ft_create_player(t_player **n_p, unsigned int *s_r, char *l,
				char *f_n);
void			ft_champion(t_data *dat, t_player **new_p, char *file_n,
				int fd);
void			ft_flags(int *index, char **argv, t_player **new_p);
void			ft_control_line(char *line, char *file_name);
char			*ft_read_champion(int fd, unsigned int *size_read,
				char *file_name);
/*
** Functions in FT_PRINT>C
*/
void			ft_print_game(t_player **begin);
void			ft_print_player(t_player *players_list);
void			ft_print_matrix(void);
/*
** Functions in FT_GAME>C
*/
void			ft_game(t_data *data, t_visu *visu);
void			ft_fight(t_proc **begin);
/*
** Functions in FT_PROCESS>C
*/
void			ft_process(t_data *data);
/*
** Functions in INSTRUCTIONS
*/
int				ft_check_op(t_proc *proc, int state);
void			ft_init_func_tab(void);
void			ft_add(t_proc *proc, t_proc **begin);
void			ft_ldi(t_proc *proc, t_proc **begin);
void			ft_lld(t_proc *proc, t_proc **begin);
void			ft_st(t_proc *proc, t_proc **begin);
void			ft_xor(t_proc *proc, t_proc **begin);
void			ft_aff(t_proc *proc, t_proc **begin);
void			ft_fork(t_proc *proc, t_proc **begin);
void			ft_lfork(t_proc *proc, t_proc **begin);
void			ft_lldi(t_proc *proc, t_proc **begin);
void			ft_sti(t_proc *proc, t_proc **begin);
void			ft_zjmp(t_proc *proc, t_proc **begin);
void			ft_and(t_proc *proc, t_proc **begin);
void			ft_ld(t_proc *proc, t_proc **begin);
void			ft_live(t_proc *proc, t_proc **begin);
void			ft_or(t_proc *proc, t_proc **begin);
void			ft_sub(t_proc *proc, t_proc **begin);
int				ft_get_number_arg(char instru, t_proc *proc);
void			ft_get_ind_value(t_proc *proc, int *j, int arg);
int				ft_get_reg_value(t_proc *proc, int *j, int arg);
/*
**	Ncurses draw functions
*/
t_draw			ft_init_draw(t_data data);
void			ft_draw_cycle(t_draw *draw, t_data *data);
int				ft_get_num_player(int id);
int				ft_got_a_process(t_proc **begin, int index);
int				ft_is_champ(int i);
void			ft_draw_general_info(t_data data, t_draw draw, t_proc **begin);

#endif
