/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trsmat4vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 21:52:33 by lbelda            #+#    #+#             */
/*   Updated: 2017/11/28 21:59:06 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmath.h"

t_mat4	trsmat4vec(t_vec4 vec)
{
	return ((t_mat4) { (t_vec4) { 1.0, 0.0, 0.0, 0.0 },
						(t_vec4) { 0.0, 1.0, 0.0, 0.0 },
						(t_vec4) { 0.0, 0.0, 1.0, 0.0 },
						(t_vec4) { vec.x, vec.y, vec.z, 1.0 }
						});
}