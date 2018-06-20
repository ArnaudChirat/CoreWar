/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:58:38 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 17:03:37 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_min(int32_t a, int32_t b)
{
	return (a > b ? b : a);
}

int32_t	ft_max(int32_t a, int32_t b)
{
	return (a < b ? b : a);
}

int32_t	ft_clamp(int32_t min, int32_t max, int32_t val)
{
	return (ft_max(ft_min(max, val), min));
}
