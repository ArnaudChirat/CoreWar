/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:48:04 by clanglai          #+#    #+#             */
/*   Updated: 2018/06/07 16:50:22 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

void	ft_error_header(t_data *data)
{
	if (!data->len)
	{
		ft_putstr_fd("Champ is empty\n", 2);
		exit(1);
	}
	if (!data->header.prog_name[0] || !data->header.comment[0])
	{
		write(2, "Header is not valid\n", 20);
		exit(1);
	}
}
