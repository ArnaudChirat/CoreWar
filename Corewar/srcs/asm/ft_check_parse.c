/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:35:21 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:35:24 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

t_op	g_op_tab[OP_NBR + 1] =
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

/*
** Fonction qui traite le .name et .comment du .s. Elle verifie qu'il y est
** bien un espace apres les deux '"', et enregistre le tout dans la struct
** t_data->header(.comment || .name).
*/

void	ft_fill_header(t_parse **tmp, t_data *data, int quotes)
{
	t_parse	*keep;

	keep = *tmp;
	(*tmp) = (*tmp)->next;
	if (ft_strequ(keep->label, COMMENT_CMD_STRING) == 1)
		data->in_comment = 1;
	while (*tmp && quotes != 2)
	{
		if (ft_strequ("\"", (*tmp)->label))
		{
			if (++quotes == 2)
				break ;
		}
		else if (quotes < 1)
			ft_parse_error(*tmp);
		else if (quotes == 1)
			ft_fill_header_2(tmp, data, keep);
		else if (quotes >= 2 && (*tmp)->type != NEW_LINE_TYPE)
			ft_parse_error(*tmp);
		*tmp = (*tmp)->next;
	}
	if (quotes != 2)
		ft_parse_error(*tmp);
}

/*
** Elle verifie qu'il y est bien le nombre associe de parametre a l'opcode.
** Ensuite regarde si il y a un octet de codage (g_op_cod[opcode].o_cod) pour
** rajouter +1 a la len.
*/

void	ft_parse_actions(t_parse **tmp, t_data *data)
{
	int		len_actu;
	int		state;

	data->nb_arg = 0;
	state = 1;
	data->separator = ft_count_separator(*tmp);
	data->occode = 0;
	data->opcode_index = data->len;
	data->bytecode[data->len++] = data->opcode--;
	if (g_op_tab[data->opcode].nb_params != data->separator + 1)
		ft_invalid_arg_error(*tmp);
	len_actu = data->len;
	data->len = g_op_tab[data->opcode].o_cod ? data->len + 1 : data->len;
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->type != NEW_LINE_TYPE)
	{
		state = ft_parse_actions_2(tmp, data, state);
		if (data->len > CHAMP_MAX_SIZE)
		{
			write(2, "File is too big to be a valid champion\n", 39);
			exit(1);
		}
	}
	if (g_op_tab[data->opcode].o_cod)
		data->bytecode[len_actu] = data->occode;
}

/*
** Sublime fonction qui saute les commentaires, ou verifie l'opcode avec le
** label et envoie le tout sur ft_parse_action, ou si l'opc et le label ne sont
** pas pareil, veifie la validite de du label, et cree un nouveau maillon
** indirect.
*/

void	ft_check_lign_parse(t_parse **tmp, t_data *d, int state, t_label *tmp_d)
{
	while (*tmp && (*tmp)->type != NEW_LINE_TYPE)
	{
		d->opcode = 0;
		if (ft_strequ((*tmp)->label, COMMENT_STR) || state == 0)
			state = 0;
		else if ((d->opcode = ft_is_op((*tmp)->label)))
			ft_parse_actions(tmp, d);
		else if (ft_is_valid_label((*tmp)->label, 0))
			if (!tmp_d)
				d->ind_label = ft_new_ind_label((*tmp)->label, d->len, 0, 0);
			else
			{
				while (tmp_d->next)
					tmp_d = tmp_d->next;
				tmp_d->next = ft_new_ind_label((*tmp)->label, d->len, 0, 0);
			}
		else if ((*tmp)->label[0] == ENDL_COMMENT_CHAR)
			while (*tmp && (*tmp)->type != NEW_LINE_TYPE)
				*tmp = (*tmp)->next;
		else if ((*tmp)->type != NEW_LINE_TYPE)
			ft_parse_error(*tmp);
		if (*tmp && (*tmp)->type != NEW_LINE_TYPE)
			*tmp = (*tmp)->next;
	}
}

/*
** Fonction qui traite les elements sauvegardes avec ft_get_instruction.
** ft_fill_header sauvegarde le .name et .comment.
** ft_check_lign_parse quand a elle, check les autres instructions.
** Les defines se trouvent dans le asm_struct.h
*/

void	ft_check_parse(t_data *data)
{
	t_parse		*tmp;

	tmp = data->parse;
	data->ind_label = NULL;
	data->stor_label = NULL;
	while (tmp)
	{
		if (ft_strequ(tmp->label, NAME_CMD_STRING) || ft_strequ(tmp->label,
					COMMENT_CMD_STRING))
			ft_fill_header(&tmp, data, 0);
		else if ((data->header.prog_name[0] != 0 &&
			data->in_comment) || ft_strequ(tmp->label, COMMENT_STR) ||
				ft_strequ(tmp->label, COMMENT_STR2))
			ft_check_lign_parse(&tmp, data, 1, data->ind_label);
		else if (tmp->type == NEW_LINE_TYPE)
			;
		else
			ft_parse_error(tmp);
		if (tmp)
			tmp = tmp->next;
	}
	ft_error_header(data);
	ft_fill_adresses(data);
}
