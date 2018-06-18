/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:22:25 by achirat           #+#    #+#             */
/*   Updated: 2018/01/30 10:07:15 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <limits.h>

static int		ft_len(char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '\n'));
	return (len);
}

static char		*cpy_res(char *str, char **line)
{
	char *tmp;

	tmp = 0;
	if (ft_strchr(str, '\n') == 0)
	{
		*line = ft_strdup(str);
		if (str)
			free(str);
		return (0);
	}
	*line = ft_strnew(ft_len(str));
	*line = ft_strncpy(*line, str, ft_len(str));
	tmp = ft_strdup(str);
	if (str)
		free(str);
	str = ft_strsub(tmp, ft_len(tmp) + 1, ft_strlen(ft_strchr(tmp, '\n')) - 1);
	if (tmp)
		free(tmp);
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static char		*res[OPEN_MAX];
	t_gnl			gnl;
	char			buff[BUFF_SIZE + 1];

	if (fd < 0 || !(line) || fd >= OPEN_MAX || BUFF_SIZE == 0)
		return (-1);
	if (!res[fd])
		res[fd] = ft_strnew(0);
	while ((gnl.ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[gnl.ret] = '\0';
		gnl.tmp = ft_strdup(res[fd]);
		free(res[fd]);
		res[fd] = ft_strjoin(gnl.tmp, buff);
		free(gnl.tmp);
		if (ft_strchr(buff, '\n') != 0)
			break ;
	}
	if (gnl.ret == -1)
		return (-1);
	if (gnl.ret == 0 && res[fd][0] == 0)
		return (0);
	res[fd] = cpy_res(res[fd], line);
	return (1);
}
