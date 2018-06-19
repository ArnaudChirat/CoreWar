/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:55:32 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/13 17:45:47 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#ifdef __APPLE__

static void	compat(void)
{
	return ;
}

#else

static void	compat(void)
{
	glewInit();
}

#endif

static void	init_sdl(t_visu *v)
{
	int	ret;

	ret = 0;
	if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO))
		error_exit(SDL_GetError());
	ret |= SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	ret |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	ret |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	ret |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
	if (ret)
		error_exit(SDL_GetError());
	if (!(v->win = SDL_CreateWindow("corewar", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, 0, 0,
					SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL)))
		error_exit("");
	SDL_GetWindowSize(v->win, &v->win_size.x, &v->win_size.y);
	v->ratio = (float)v->win_size.x / (float)v->win_size.y;
	if (!(v->context = SDL_GL_CreateContext(v->win)))
		error_exit(SDL_GetError());
}

t_visu	init_visu(t_data *data)
{
	t_visu	v;

	ft_bzero(&v, sizeof(t_visu));
	init_sdl(&v);
	compat();
	v.matrices = init_matrices();
	v.controls = init_controls();
	init_scene(&v, *data);
	glClearColor(0., 0., 0., 1.);
	glViewport(0, 0, v.win_size.x, v.win_size.y);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return (v);
}
