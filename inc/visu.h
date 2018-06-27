/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:56:47 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 02:24:34 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
# else
#  include <GL/glew.h>
# endif

# include <time.h>
# include <pthread.h>

# include "SDL.h"
# include "libft.h"
# include "libftmath.h"

# include "v_matrices.h"
# include "v_controls.h"
# include "v_sound.h"
# include "v_ogl_utils.h"

# include "vm.h"

# define CT_WIDTH -96

# define INC_CPF 0.03
# define INIT_CPF 1.0
# define MIN_CPF 0.1
# define MAX_CPF 20.

enum			e_progs
{
	PROG_BG,
	PROG_TXT,
	PROG_TXT_PL1,
	PROG_TXT_PL2,
	PROG_TXT_PL3,
	PROG_TXT_PL4,
	PROG_CT,
	PROG_PLN,
	PROG_PL1,
	PROG_PL2,
	PROG_PL3,
	PROG_PL4,
	PROG_MAX
};

enum			e_players
{
	P_N,
	P_1,
	P_2,
	P_3,
	P_4,
	P_MAX
};

enum			e_phases
{
	PH_INTRO,
	PH_GAME,
	PH_FINAL,
	PH_MAX
};

enum			e_3d_alphabet
{
	A_ALPHA = 0,
	A_NUM = 26,
	A_UNDERSCORE = 36,
	A_MAX
};

typedef struct	s_background
{
	GLuint	program;
	GLuint	vao;
	GLuint	vbo;
	GLuint	ibo;
}				t_background;

enum			e_text_fields
{
	TXT_CYC,
	TXT_PL1,
	TXT_PL2,
	TXT_PL3,
	TXT_PL4,
	TXT_PL1_PROC,
	TXT_PL2_PROC,
	TXT_PL3_PROC,
	TXT_PL4_PROC,
	TXT_PL1_LIVE,
	TXT_PL2_LIVE,
	TXT_PL3_LIVE,
	TXT_PL4_LIVE,
	TXT_PL1_PN,
	TXT_PL2_PN,
	TXT_PL3_PN,
	TXT_PL4_PN,
	TXT_PL1_LN,
	TXT_PL2_LN,
	TXT_PL3_LN,
	TXT_PL4_LN,
	TXT_MAX
};

typedef struct	s_text_field
{
	GLuint		program;
	GLuint		vao;
	GLuint		vbo;
	GLuint		ibo;
	t_glfloat3	world_pos;
	GLint		u_world_pos;
	float		model_rot;
	GLint		u_model_rot;
	float		scale;
	GLint		u_scale;
	t_mesh		mesh;
}				t_text_field;

typedef struct	s_text_data
{
	t_glfloat3	pos[TXT_MAX];
	float		rot[TXT_MAX];
	float		scale[TXT_MAX];
}				t_text_data;

typedef struct	s_v_arena
{
	char		*shader_paths[(MAX_PLAYERS + 1) * 2];
	GLuint		programs[MAX_PLAYERS + 1];
	GLuint		vaos[MAX_PLAYERS + 1];
	GLuint		vbos_inst[MAX_PLAYERS + 1];
	t_glfloat3	*data_inst[MAX_PLAYERS + 1];
	t_glfloat3	*arena_coords;
	int			nb_instances[MAX_PLAYERS + 1];
	GLuint		vbo_mesh;
	GLuint		ibo_mesh;
	t_mesh		mesh;
	int			nb_players;
}				t_v_arena;

enum			e_vbos_ct
{
	VBO_CT_MESH,
	VBO_CT_MAX
};

typedef struct	s_counters
{
	GLuint		program;
	GLuint		vao;
	GLuint		vbos[VBO_CT_MAX];
	GLuint		ibo;
	t_mesh		mesh;
	int			nb_players;
}				t_counters;

enum			e_ubo_main_sizes
{
	U_MAIN_FINALMAT,
	U_MAIN_RES = U_MAIN_FINALMAT + sizeof(t_mat4),
	U_MAIN_RATIO = U_MAIN_RES + sizeof(t_vec2),
	U_MAIN_TIME = U_MAIN_RATIO + sizeof(float),
	U_MAIN_INTRO = U_MAIN_TIME + sizeof(float),
	U_MAIN_BASS = U_MAIN_INTRO + sizeof(float),
	U_MAIN_SPEED = U_MAIN_BASS + sizeof(float),
	U_MAIN_TOT = U_MAIN_SPEED + sizeof(float)
};

enum			e_ubo_raymarch_sizes
{
	U_RM_EYE,
	U_RM_TOT = U_RM_EYE + sizeof(t_vec3)
};

enum			e_ubos
{
	UBO_MAIN,
	UBO_RM,
	UBO_MAX
};

typedef struct	s_ublock
{
	GLuint	progs_id[PROG_MAX];
	GLuint	ubo;
}				t_ublock;

typedef struct	s_events
{
	struct timespec	origin;
	struct timespec	current;
	float			time;
	float			intro;
	char			phase;
}				t_events;

typedef struct	s_scene
{
	t_events		events;
	t_background	background;
	t_v_arena		arena;
	t_counters		counters;
	t_mesh			alphabet_3d[A_MAX];
	t_text_field	texts[TXT_MAX];
	t_text_data		texts_data;
	t_ublock		ublocks[UBO_MAX];
	GLuint			all_programs[PROG_MAX];
	int				pl_on[MAX_PLAYERS];
	int				nb_process[MAX_PLAYERS];
	int				nb_lives[MAX_PLAYERS];
}				t_scene;

typedef struct	s_visu
{
	SDL_GLContext	context;
	SDL_Window		*win;
	t_vec2r			win_size;
	float			ratio;
	t_controls		controls;
	t_matrices		matrices;
	t_scene			scene;
	t_sound			sound;
	float			speed;
	float			cyc_per_frame;
	float			cyc_per_frame_inc;
	int				frame_since_refresh;
	int				pause;
	int				quit;
}				t_visu;

t_visu			*init_visu(t_data *data);
void			init_scene(t_visu *v, t_data data);
void			init_3d_alphabet(t_mesh *alphabet);
void			create_text_data(t_text_data *data);
void			init_text(t_text_field *texts, t_mesh *alphabet,
								t_data d, char **shader_paths);
void			init_text_info(t_text_field *texts, t_mesh *alphabet,
								t_data d, GLuint program);
void			init_text_info_nb(t_text_field *texts, GLuint program);
t_mesh			str_to_mesh(const char *str, t_mesh *alphabet);
void			text_rotation(t_mesh text, float angle);
void			init_text_buffers(t_text_field *text);
void			init_text_buffers_empty(t_text_field *text);
t_v_arena		init_arena(t_data data);
void			init_arena_data(t_v_arena *a, t_data data);
t_mesh			create_arena_mesh(void);
t_counters		init_counters(t_data d);
t_mesh			create_counter_mesh(void);
void			init_ublocks(t_visu v, t_ublock *u);

void			render(t_visu *v, t_data *d);

t_events		init_clock(void);
void			handle_events(t_visu *v);
void			update_clock(t_visu *v, t_events *e);
void			update_camera(t_matrices *mat);
void			update_uniforms(t_visu v);
void			render_counters(t_counters c, t_events e);
void			update_counters(t_counters *c, t_data *d);
void			update_arena(t_v_arena *a, t_data *d);
void			render_arena(t_v_arena a);
void			update_text_info(t_scene *scene, t_data *d);
void			render_text(t_text_field *texts, t_text_data txt_data,
									t_events e, int *pl_on);

void			ft_free_visu(t_visu *v);
void			free_scene(t_scene *scene);
void			free_mesh(t_mesh *mesh);
void			free_text_field(t_text_field *txt);
void			error_exit(const char *str);

#endif
