/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:47:35 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 14:47:37 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Fonctions de verification du header
*/

char	*ft_read_champion(int fd, unsigned int *size_read, char *file_name)
{
	int		ret;
	char	*line;
	char	buffer[COR_MAX_SIZE];

	while ((ret = read(fd, buffer, COR_MAX_SIZE)) > 0
			&& *size_read <= HEADER_MAX_SIZE + CHAMP_MAX_SIZE)
		*size_read += ret;
	if (*size_read > CHAMP_MAX_SIZE + HEADER_MAX_SIZE)
	{
		ft_putstr_fd("Error : File ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(" is too big to be a champion\n", 2);
		exit(1);
	}
	if (*size_read < HEADER_MAX_SIZE)
		ft_error(1, "File is too small to be a champion", 0, 0);
	if (ret == -1)
		ft_error(0, "Read failled in ft_read_champion", 0, 0);
	if (*size_read > COR_MAX_SIZE)
		ft_error(4, file_name, *size_read - HEADER_MAX_SIZE, CHAMP_MAX_SIZE);
	if (!(line = ft_strnew(*size_read)) || lseek(fd, 0, SEEK_SET) == -1)
		ft_error(0, "Malloc failed in ft_read_champion (char *line)", 0, 0);
	if (read(fd, line, *size_read) == -1)
		ft_error(0, "Read failled in ft_read_champion", 0, 0);
	return (line);
}

void	ft_control_line(char *line, char *file_name)
{
	int			increment;
	static int	index = MAGIC_LENGTH + PROG_NAME_LENGTH - 4;

	increment = 0;
	while (increment < 4)
	{
		if (line[index + increment] != 0)
			ft_error(5, file_name, 0, 0);
		increment++;
	}
	if (index + increment == HEADER_MAX_SIZE)
		return ;
	index = HEADER_MAX_SIZE - 4;
	ft_control_line(line, file_name);
}
