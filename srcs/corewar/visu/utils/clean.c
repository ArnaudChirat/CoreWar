/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 11:38:32 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/02 11:41:21 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_free_visu(t_visu *v)
{
	SDL_GL_DeleteContext(v->context);
	SDL_DestroyWindow(v->win);
	SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	SDL_Quit();
}
