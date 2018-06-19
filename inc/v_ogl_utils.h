/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ogl_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 10:29:13 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/06 18:32:42 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_OGL_UTILS_H
# define V_OGL_UTILS_H

# ifdef __APPLE__
#  include <OpenGL/gl3.h>
# else
#  include <GL/glew.h>
# endif

# include "v_common.h"
# include "libft.h"
# include "printf.h"
# include "fcntl.h"

typedef struct	s_glfloat2
{
	GLfloat	x;
	GLfloat	y;
}				t_glfloat2;

typedef struct	s_glfloat3
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;
}				t_glfloat3;

typedef struct	s_tri_ind
{
	GLuint	a;
	GLuint	b;
	GLuint	c;
}				t_tri_ind;

typedef struct	s_mesh
{
	t_glfloat3	*coords;
	int			nb_vtx;
	t_tri_ind	*indices;
	GLuint		*indices_uni;
	int			nb_triangles;
	int			nb_indices;
}				t_mesh;

GLuint			build_ogl_program(const char *vtx_path, const char *frag_path);

char			*parse_shader(const char *shader_path);
void			print_compile_errors(GLuint shader, int exit);
void			print_link_errors(GLuint program);
void			check_glerror(void);

#endif
