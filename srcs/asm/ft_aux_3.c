/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:34:46 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 18:12:06 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

/*
**	Checke que rien ne suit les parametres
*/

void	ft_fill_header_2(t_parse **tmp, t_data *data, t_parse *keep)
{
	if (ft_strequ(keep->label, NAME_CMD_STRING))
	{
		if (ft_strlen(data->header.prog_name) +
				ft_strlen((*tmp)->label) > PROG_NAME_LENGTH)
		{
			ft_putstr_fd("Champion name is too long\n", 2);
			exit(1);
		}
		ft_strcat(data->header.prog_name, (*tmp)->label);
	}
	else
	{
		if (ft_strlen(data->header.comment) +
				ft_strlen((*tmp)->label) > COMMENT_LENGTH)
		{
			ft_putstr_fd("Champion omment is too long\n", 2);
			exit(1);
		}
		ft_strcat(data->header.comment, (*tmp)->label);
	}
}

/*
** Fonction qui compte le nombre de virgule danas la struct t_parse->label
** (separateur d'arguement).
*/

int		ft_count_separator(t_parse *tokens)
{
	t_parse *tmp;
	int		res;

	tmp = tokens;
	res = 0;
	while (tmp && tmp->type != NEW_LINE_TYPE && tmp->type != COMMENT_CHAR_TYPE
			&& !ft_strequ(tmp->label, COMMENT_STR2))
	{
		if (ft_strequ(",", tmp->label))
			res++;
		tmp = tmp->next;
	}
	return (res);
}

void	ft_check_next_param(t_parse *parse)
{
	if (parse->next)
	{
		if (parse->next->type != NEW_LINE_TYPE
				&& !ft_strequ(parse->next->label, ",")
				&& !ft_strequ(parse->next->label, COMMENT_STR)
				&& !ft_strequ(parse->next->label, COMMENT_STR2))
		{
			ft_parse_error(parse->next);
		}
	}
}

/*
**	Gere l'enregistrement des unicodes dans les names et comment
*/

int		ft_char_unicode(char c)
{
	int nb;

	nb = 0;
	while ((wchar_t)c >> nb && nb < 10)
		nb++;
	if (nb < 8)
		return (0);
	return (1);
}

/*
** Fonction qui verifie si c'est bien un OPCODE valide.
** Il retourne son OPCODE ou 0 au choix.
*/

int		ft_is_op(char *str)
{
	int	i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, str))
			return (g_op_tab[i].opcode);
		i++;
	}
	return (0);
}
