/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:36:31 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:36:33 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

/*
**	Fonction qui tri les tokens.
**	Un token etant une sequence de caracteres lue par la machine.
*/

char	*ft_cut_token(char *str, int i, int *len)
{
	char	*res;

	while (str[i + *len] && (ft_is_separator(str[i + *len], 0) < 2))
		(*len)++;
	*len = *len == 0 ? 1 : *len;
	if (!(res = ft_strsub(str, i, *len)))
		exit(1);
	return (res);
}

/*
**	Fonction qui coupe les mots ou caractere speciaux(token).
*/

t_parse	*ft_cut_words(int *i, int lign, char *str)
{
	char	*res;
	int		len;

	len = 0;
	while (str[*i])
	{
		if (ft_is_separator(str[*i], 0))
		{
			res = ft_cut_token(str, *i, &len);
			*i = *i + len - 1;
			return (ft_new_parse(*i - len + 1, lign, res,
						ft_is_separator(str[*i], 0)));
		}
		(*i)++;
	}
	(*i)--;
	return (ft_new_parse(*i, lign, ft_strdup("\n"), NEW_LINE_TYPE));
}

/*
**	Fonction de parsing des mots et caractere speciaux.
**	Ils sont ensuite sauvegardes dans la struct t_parse.
*/

void	ft_parse_line(t_parse **parse, char *str, int lign, t_data *data)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_is_separator(str[i], 1) != 2)
		{
			if (*parse == NULL)
				*parse = ft_cut_words(&i, lign, str);
			else
				ft_get_last_elem(parse)->next = ft_cut_words(&i, lign, str);
			ft_min_check(ft_get_last_elem(parse), data);
		}
		i++;
	}
	if (*parse == NULL)
		*parse = ft_cut_words(&i, lign, str);
	else
		ft_get_last_elem(parse)->next = ft_cut_words(&i, lign, str);
	ft_min_check(ft_get_last_elem(parse), data);
}

/*
**	Fonction qui lis les intstructions.
**	Elle traite le cas d'envoi d'un fichier vide.
*/

void	ft_get_instructions(int fd_r, t_parse **parse, t_data *data)
{
	char	*line;
	int		i;
	t_parse	*tmp;
	t_parse *next;

	i = 1;
	next = NULL;
	line = NULL;
	while (get_next_line(fd_r, &line) > 0)
	{
		if (line)
			ft_parse_line(parse, line, i++, data);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	tmp = *parse;
	ft_get_instructions_2(tmp, next);
	if (i == 0)
	{
		write(2, "File is empty\n", 14);
		exit(1);
	}
	i = 0;
}
