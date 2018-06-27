/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 10:55:32 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 06:31:58 by lbelda           ###   ########.fr       */
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

static void	init_shared_vars(t_visu *v)
{
	v->quit = 0;
	v->pause = 0;
}

t_visu		*init_visu(t_data *data)
{
	t_visu	*v;

	m_pro_null(v = ft_memalloc(sizeof(t_visu)));
	if (!data->flag_v)
	{
		init_shared_vars(v);
		return (v);
	}
	init_sdl(v);
	compat();
	v->matrices = init_matrices();
	v->controls = init_controls();
	v->sound = init_sound();
	v->cyc_per_frame = INIT_CPF;
	v->cyc_per_frame_inc = 1.;
	v->pause = 1;
	init_scene(v, *data);
	glClearColor(0., 0., 0., 1.);
	glViewport(0, 0, v->win_size.x, v->win_size.y);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	v->scene.events = init_clock();
	launch_music(&v->sound);
	return (v);
}
