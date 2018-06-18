/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:36:39 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:36:41 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

static int	ft_is_valid_min_label(char *str)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	while (str[i])
	{
		j = 0;
		state = 0;
		while (LABEL_CHARS[j])
		{
			if (LABEL_CHARS[j] == str[i] || str[i] == LABEL_CHAR)
			{
				state = 1;
				break ;
			}
			j++;
		}
		if (state == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_min_check_2(t_parse *tmp, t_data *data)
{
	int	i;

	if (ft_strequ(tmp->label, "\""))
		data->quotes = data->quotes == 1 ? 0 : 1;
	if (ft_strequ(tmp->label, COMMENT_STR) ||
			ft_strequ(tmp->label, COMMENT_STR2))
		data->comment = 1;
	if (tmp->type == NEW_LINE_TYPE)
		data->comment = 0;
	i = 0;
	while (i < OP_NBR)
		if (ft_strequ(tmp->label, g_op_tab[i++].name))
			return (1);
	return (0);
}

void		ft_min_check(t_parse *tmp, t_data *data)
{
	if (ft_min_check_2(tmp, data))
		return ;
	if (data->quotes == 0 && data->comment == 0)
	{
		if (ft_strequ(".name", tmp->label) && !data->name_token)
			data->name_token = 1;
		else if (ft_strequ(".comment", tmp->label) && !data->comment_token)
			data->comment_token = 1;
		else if (ft_is_separator(tmp->label[0], 0) > 1 ||
				tmp->type == NEW_LINE_TYPE)
			;
		else if (ft_isnumber(tmp->label))
			;
		else if ((ft_strlen(tmp->label) == 2 || ft_strlen(tmp->label) == 3)
				&& tmp->label[0] == 'r' && ft_isdigit(tmp->label[1]))
			;
		else if (!ft_is_valid_min_label(tmp->label))
			ft_parse_error(tmp);
	}
}
