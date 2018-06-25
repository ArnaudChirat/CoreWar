/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_controls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:18:46 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/25 17:14:54 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_CONTROLS_H
# define V_CONTROLS_H

# include "SDL.h"

enum			e_kb_funcs
{
	KB_RIGHT,
	KB_LEFT,
	KB_DOWN,
	KB_UP,
	KB_D,
	KB_A,
	KB_S,
	KB_W,
	KB_P,
	KB_E,
	KB_SPACE,
	KB_ESCAPE,
	KB_MAX
};

enum			e_ps3_funcs
{
	PS3_AXIS_LEFTY,
	PS3_AXIS_LEFTX,
	PS3_AXIS_TRIGGERLEFT,
	PS3_AXIS_TRIGGERRIGHT,
	PS3_MAX
};

typedef struct	s_kb_lookup
{
	SDL_Keycode	sym;
	void		(*func)(void *v, int type);
}				t_kb_lookup;

typedef struct	s_ps3_lookup
{
	uint8_t		axis;
	void		(*func)(void *v, int16_t value);
}				t_ps3_lookup;

typedef struct	s_controls
{
	t_kb_lookup			kb_lookup[KB_MAX];
	t_ps3_lookup		ps3_lookup[PS3_MAX];
	SDL_GameController	*ps3_id;
}				t_controls;

t_controls		init_controls(void);

void			kb_right(void *v, int type);
void			kb_left(void *v, int type);
void			kb_down(void *v, int type);
void			kb_up(void *v, int type);
void			kb_speed_up(void *v, int type);
void			kb_speed_down(void *v, int type);
void			kb_pause(void *v, int type);
void			kb_quit(void *v, int type);
void			kb_debug(void *v, int type);
void			kb_none(void *v, int type);

void			ps3_xtrs(void *v, int16_t value);
void			ps3_ytrs(void *v, int16_t value);
void			ps3_speed_up(void *v, int16_t value);
void			ps3_speed_down(void *v, int16_t value);

#endif
