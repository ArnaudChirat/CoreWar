/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:35:39 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:35:41 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

/*
** Transformation du parametre direct en hexa.
*/

void	ft_fill_direct_param(t_data *data, int a, int opcode)
{
	if (g_op_tab[opcode].dir_addr == 1)
	{
		data->bytecode[data->len++] = (char)(a >> 8 & 0xff);
		data->bytecode[data->len++] = (char)(a & 0xff);
	}
	else
	{
		data->bytecode[data->len++] = (char)(a >> 24 & 0xff);
		data->bytecode[data->len++] = (char)(a >> 16 & 0xff);
		data->bytecode[data->len++] = (char)(a >> 8 & 0xff);
		data->bytecode[data->len++] = (char)(a & 0xff);
	}
}

/*
** La premiere partie de la fonction sert a creer un nouveau maillon.
** La seconde partie creer la place pour le parametre direct.
*/

t_parse	*check_param_direct(t_parse *parse, int nbr_arg, t_data *d, int a)
{
	t_label	*tmp_d;

	tmp_d = d->stor_label;
	if (!ft_isnumber(parse->label))
	{
		if (!tmp_d)
			d->stor_label = ft_new_ind_label(parse->label,
					d->opcode_index, d->len, g_op_tab[d->opcode].dir_addr);
		else
		{
			while (tmp_d->next)
				tmp_d = tmp_d->next;
			tmp_d->next = ft_new_ind_label(parse->label, d->opcode_index,
					d->len, g_op_tab[d->opcode].dir_addr == 1);
		}
	}
	else
		a = ft_atoi(parse->label);
	if ((g_op_tab[d->opcode].param_type[nbr_arg] & T_DIR) == T_DIR)
		d->occode += (char)(0x80 >> (nbr_arg * 2));
	else
		ft_parse_error(parse);
	ft_fill_direct_param(d, a, d->opcode);
	ft_check_next_param(parse);
	return (parse->next);
}

/*
** Verifie le parametre indirect et le transforme en hexa.
*/

t_parse	*check_param_ind(t_parse *p, int nbr_arg, t_data *d, t_label *t_d)
{
	int a;

	a = 0;
	if (!ft_isnumber(p->label))
	{
		if (!t_d)
			d->stor_label = ft_new_ind_label(p->label,
					d->opcode_index, d->len, 1);
		else
		{
			while (t_d->next)
				t_d = t_d->next;
			t_d->next = ft_new_ind_label(p->label, d->opcode_index, d->len, 1);
		}
	}
	else
		a = ft_atoi(p->label);
	if ((g_op_tab[d->opcode].param_type[nbr_arg] & T_IND) == T_IND)
		d->occode += (char)(0xc0 >> (nbr_arg * 2));
	else
		ft_parse_error(p);
	d->bytecode[d->len++] = (char)(a >> 8 & 0xff);
	d->bytecode[d->len++] = (char)(a & 0xff);
	ft_check_next_param(p);
	return (p->next);
}

/*
** Verifie le registre (si plus de 16 ou si ce n'est pas un nombre).
** le tranforme en hexa.
*/

void	check_param_reg(t_parse *parse, int nbr_arg, t_data *data)
{
	int a;

	a = ft_atoi(parse->label + 1);
	if (ft_isnumber(parse->label + 1) == 0 || a > 16)
		ft_parse_error(parse);
	if ((g_op_tab[data->opcode].param_type[nbr_arg] & T_REG) == T_REG)
		data->occode += (char)(0x40 >> (nbr_arg * 2));
	else
		ft_parse_error(parse);
	ft_check_next_param(parse);
	data->bytecode[data->len++] = (char)(a & 0xff);
}

/*
** Verifie les parametres, direct, indirect, et registre.
*/

int		ft_parse_actions_2(t_parse **tmp, t_data *data, int state)
{
	if ((*tmp)->label[0] == ENDL_COMMENT_CHAR || state == 0 || (*tmp)->type
			== COMMENT_CHAR_TYPE)
	{
		*tmp = (*tmp)->next;
		return (0);
	}
	else if ((*tmp)->label[0] == SEPARATOR_CHAR && (*tmp)->label[1] == '\0')
		;
	else if ((*tmp)->label[0] == DIRECT_CHAR && (*tmp)->label[1] == '\0')
		*tmp = check_param_direct((*tmp)->next, data->nb_arg++, data, 0);
	else if ((*tmp)->label[0] == 'r')
		check_param_reg(*tmp, data->nb_arg++, data);
	else if (ft_isnumber((*tmp)->label) || (*tmp)->label[0] == LABEL_CHAR)
		*tmp = check_param_ind(*tmp, data->nb_arg++, data, data->stor_label);
	else
		ft_parse_error(*tmp);
	if ((*tmp)->type == COMMENT_CHAR_TYPE)
		state = 0;
	if (tmp && (*tmp)->type != NEW_LINE_TYPE && ((*tmp)->type
				!= ENDL_COM_TYPE || state == 0))
		*tmp = (*tmp)->next;
	return (state);
}
