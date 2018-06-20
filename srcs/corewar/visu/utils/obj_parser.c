/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 13:57:09 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/20 13:57:04 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_obj_parser.h"

static void		parse_split(t_mesh *p, char **split)
{
	if (split[0][0] == 'v')
	{
		p->nb_vtx++;
		m_pro_null(p->coords = realloc(p->coords,
					sizeof(t_glfloat3) * p->nb_vtx));
		p->coords[p->nb_vtx - 1] =
			(t_glfloat3){atof(split[1]), atof(split[2]), atof(split[3])};
	}
	else if (split[0][0] == 'f')
	{
		p->nb_triangles++;
		m_pro_null(p->indices = realloc(p->indices,
					sizeof(t_tri_ind) * p->nb_triangles));
		p->indices[p->nb_triangles - 1] =
			(t_tri_ind){ft_atoi(split[1]) - 1, ft_atoi(split[2]) - 1,
										ft_atoi(split[3]) - 1};
	}
}

static void		parse_line(t_mesh *p, const char *line)
{
	char	**split;
	int		split_size;

	split = ft_strsplit(line, ' ');
	split_size = 0;
	while (split[split_size])
		split_size++;
	if (split_size != 4)
	{
		ft_tabdel(&split);
		return ;
	}
	parse_split(p, split);
	ft_tabdel(&split);
}

t_mesh			obj_parser(const char *path)
{
	int		fd;
	int		ret;
	char	*line;
	t_mesh	p;

	line = NULL;
	ft_bzero(&p, sizeof(t_mesh));
	if ((fd = open(path, O_RDONLY)) == -1)
		error_exit("");
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1 || !line)
			error_exit("get_next_line failed");
		parse_line(&p, line);
		free_pro((void**)&line);
	}
	free_pro((void**)&line);
	p.nb_indices = p.nb_triangles * 3;
	if (close(fd) == -1)
		error_exit("");
	return (p);
}
