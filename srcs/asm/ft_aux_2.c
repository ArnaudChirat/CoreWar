/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:34:38 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:34:40 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

/*
** Fonction qui extrait le nom du joueur, ajoute le .cor.
** Elle donne le nom final du fichier de sortie.
*/

char	*ft_get_name(char *str, int i, int len, int slash)
{
	char	*new;
	char	*tmp;

	while (str[i])
	{
		if (str[i] == '.')
			len = i;
		if (str[i] == '/')
			slash = i;
		i++;
	}
	if (slash < len)
	{
		if (!(tmp = ft_strsub(str, 0, len)))
			exit(1);
		if (!(new = ft_strjoin(tmp, ".cor")))
			exit(1);
		free(tmp);
	}
	else
	{
		if (!(new = ft_strjoin(str, ".cor")))
			exit(1);
	}
	return (new);
}

int		ft_is_valid_label_2(char *str, int state)
{
	if (state == 0)
	{
		if (str[ft_strlen(str) - 1] != ':' || !ft_is_valid_label(str, state))
			return (0);
	}
	else
	{
		if (str[0] != ':' || !ft_is_valid_label(str + 1, state))
			return (0);
	}
	return (1);
}

t_label	*ft_new_ind_label(char *str, int index, int state, int len)
{
	t_label *new;

	if (!(new = malloc(sizeof(t_label))))
		exit(1);
	if (state == 0)
	{
		if (!(new->label = ft_strsub(str, 0, ft_strlen(str) - 1)))
			exit(1);
	}
	else
	{
		if (!(new->label = ft_strsub(str, 1, ft_strlen(str) - 1)))
			exit(1);
	}
	if (!ft_is_valid_label_2(str, state))
	{
		ft_putstr_fd("Invalid label", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	new->len = len;
	new->state = state;
	new->index = index;
	new->next = NULL;
	return (new);
}

void	ft_fill_adresses_2(t_label *tmp, t_label *tmp2, t_data *data)
{
	int res;

	res = ((tmp2->index - tmp->index));
	if (tmp->len)
	{
		data->bytecode[tmp->state] = (char)(res >> 8 & 0xff);
		data->bytecode[tmp->state + 1] = (char)(res & 0xff);
	}
	else
	{
		data->bytecode[tmp->state] = (char)(res >> 24 & 0xff);
		data->bytecode[tmp->state + 1] = (char)(res >> 16 & 0xff);
		data->bytecode[tmp->state + 2] = (char)(res >> 8 & 0xff);
		data->bytecode[tmp->state + 3] = (char)(res & 0xff);
	}
}

void	ft_fill_adresses(t_data *data)
{
	t_label *tmp;
	t_label *tmp2;
	int		state;

	tmp = data->stor_label;
	while (tmp)
	{
		state = 0;
		tmp2 = data->ind_label;
		if (tmp2)
			while (tmp2)
			{
				if (ft_strequ(tmp2->label, tmp->label))
				{
					state = 1;
					ft_fill_adresses_2(tmp, tmp2, data);
					break ;
				}
				tmp2 = tmp2->next;
			}
		if (state == 0)
			ft_invalid_label(tmp->label);
		tmp = tmp->next;
	}
}
