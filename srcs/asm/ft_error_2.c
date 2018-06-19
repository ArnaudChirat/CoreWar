/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:36:08 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:36:10 by achirat          ###   ########.fr       */
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
