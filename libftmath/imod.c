/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:31:40 by lbelda            #+#    #+#             */
/*   Updated: 2017/12/10 19:34:34 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmath.h"

int	imod(int a, int b)
{
	int	rem;

	rem = a % b;
	return (rem < 0 ? rem + b : rem);
}
