/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3d_alphabet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 11:28:29 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/26 13:16:09 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_ogl_utils.h"
#include "v_obj_parser.h"
#include "visu.h"

#define PATH_SIZE 128
#define PATH_PREFIX "res/models/"
#define PATH_SUFFIX ".obj"

void	init_3d_alphabet(t_mesh *alphabet)
{
	char	path[PATH_SIZE];
	char	letter;
	int		i;
	int		i_letter;

	ft_bzero(path, PATH_SIZE);
	letter = 'a';
	i = 0;
	i_letter = ft_strlen(PATH_PREFIX);
	ft_strcpy(path, PATH_PREFIX);
	ft_strcpy(&path[i_letter + 1], PATH_SUFFIX);
	while (i < A_MAX)
	{
		path[i_letter] = letter;
		alphabet[i] = obj_parser(path);
		if (letter == 'z')
			letter = '0';
		else if (letter == '9')
			letter = '_';
		else
			letter++;
		i++;
	}
}
