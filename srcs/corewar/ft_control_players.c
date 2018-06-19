/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_players.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:17:50 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/08 10:03:01 by mjoubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

static void		ft_control_char(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, str[index]) == 0)
			ft_error("Wrong char in labels");
		if (ft_isprint(str[index]) == 0)
			ft_error("Error in champion name");
		index++;
	}
}

static void		ft_control_magic_numer(unsigned int magic_nbr)
{
	size_t		size_magic;
	size_t		size_define_magic;

	size_magic = 1;
	while (COREWAR_EXEC_MAGIC >> size_define_magic)
		size_define_magic++;
	while (magic_nbr >> size_magic)
		size_magic++;
	if (size_magic > size_define_magic)
		ft_error("Error magic number");
	if (magic_nbr != COREWAR_EXEC_MAGIC)
		ft_error("Error in magic number");
}
