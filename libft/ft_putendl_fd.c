/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:35:32 by achirat           #+#    #+#             */
/*   Updated: 2017/11/15 10:48:40 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *c, int fd)
{
	if (!c)
	{
		write(1, "(null)", 6);
		return ;
	}
	ft_putstr_fd(c, fd);
	ft_putchar_fd('\n', fd);
}