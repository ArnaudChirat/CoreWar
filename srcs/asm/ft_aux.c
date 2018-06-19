/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:34:28 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 18:12:26 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int		ft_isnumber(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

t_parse	*ft_get_last_elem(t_parse **list)
{
	t_parse *tmp;

	tmp = *list;
	if (*list)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

/*
**	Fonction qui verifie les separateurs, se referer au op.h
**	Son but et d'avancer sur les espaces et les tabulations.
*/

int		ft_is_separator(char c, int state)
{
	static int	i = 0;

	if (ft_char_unicode(c) == 1)
		return (1);
	if ((c == ' ' || c == '\t') && i == 0)
		return (2);
	if (c == COMMENT_CHAR && i == 0)
		return (COMMENT_CHAR_TYPE);
	if (c == DIRECT_CHAR && i == 0)
		return (DIRECT_CHAR_TYPE);
	if (c == SEPARATOR_CHAR && i == 0)
		return (SEPARATOR_CHAR_TYPE);
	if (c == '"')
	{
		if (i == 0 && state == 1)
			i = 1;
		else if (i == 1 && state == 1)
			i = 0;
		return (QUOTE_TYPE);
	}
	if (c == ENDL_COMMENT_CHAR && i == 0)
		return (ENDL_COM_TYPE);
	if (ft_isprint(c))
		return (1);
	return (0);
}

/*
**	Fonction qui cree un nouveau maillon de la struct t_parse.
*/

t_parse	*ft_new_parse(int col, int lign, char *label, int type)
{
	t_parse *new;

	if (!(new = malloc(sizeof(t_parse))) || !label)
		exit(1);
	new->next = NULL;
	new->col = col > 0 ? col : 0;
	new->label = label;
	new->lig = lign;
	new->type = type;
	return (new);
}

int		ft_is_valid_label(char *str, int state)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(str) == 1)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i] != LABEL_CHARS[j] && LABEL_CHARS[j])
			j++;
		if (!LABEL_CHARS[j])
			break ;
		i++;
	}
	if ((state && str[i] == '\0') || (str[i] == ':' && str[i + 1] == '\0'))
		return (1);
	else
		return (0);
}
