/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:40:17 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 16:40:18 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../libft/includes/libft.h"
# include "asm_struct.h"
# include "errno.h"

/*
**	Error Functions
*/
void	ft_print_error(char *str);
void	ft_print_usage(char **argv);
void	ft_invalid_label(char *str);
void	ft_invalid_arg_error(t_parse *parse);
void	ft_parse_error(t_parse *parse);
void	ft_error_header(t_data *data);

/*
**	First Parse functions
*/
void	ft_get_instructions(int fd_r, t_parse **parse, t_data *data);
void	ft_get_instructions_2(t_parse *tmp, t_parse *next);
int		ft_is_valid_label_2(char *str, int state);
void	ft_write_tab(char **tab, int d_w);
void	ft_min_check(t_parse *tmp, t_data *data);
t_parse *ft_new_parse(int col, int lign, char *label, int type);
t_parse *ft_get_last_elem(t_parse **list);
int		ft_is_valid_label(char *str, int state);
int		ft_count_separator(t_parse *token);
void	ft_check_parse(t_data *data);

/*
**	Second parse et code writing instructions
*/
void	ft_fill_header(t_parse **tmp, t_data *data, int quotes);
void	ft_fill_header_2(t_parse **tmp, t_data *data, t_parse *keep);
void	ft_parse_actions(t_parse **tma, t_data *data);
int		ft_parse_actions_2(t_parse **tmp, t_data *data, int state);
void	ft_check_lign_parse(t_parse **tmp, t_data *data, int state, t_label *t);
t_parse	*check_param_ind(t_parse *parse, int nbr_arg, t_data *data, t_label *d);
t_parse	*check_param_dir(t_parse *parse, int nbr_arg, t_data *d, int a);
void	ft_fill_direct_param(t_data *data, int a, int opcode);
void	check_param_reg(t_parse *parse, int nbr_arg, t_data *data);
void	ft_fill_adresses(t_data *data);

/*
**	Auxiiliary functions
*/
int		ft_isnumber(char *str);
t_label	*ft_new_ind_label(char *str, int index, int state, int len);
int		ft_get_adress_from_label(t_parse *parse, char *str, t_data *data);
char	*ft_get_name(char *str, int i, int len, int slash);
int		ft_is_op(char *str);
void	ft_free_data(t_data data);
int		ft_is_separator(char c, int state);
int		ft_char_unicode(char c);
void	ft_write_header(int fd_w, t_data data);
void	ft_fill_header_2(t_parse **tmp, t_data *data, t_parse *keep);
void	ft_check_next_param(t_parse *tmp);

#endif
