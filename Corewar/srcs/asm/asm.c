/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:48:36 by clanglai          #+#    #+#             */
/*   Updated: 2018/06/07 16:42:54 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

int	main(int argc, char **argv)
{
	int			fd_r;
	int			fd_w;
	t_data		data;
	char		*new;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 2)
		ft_print_usage(argv);
	if ((fd_r = open(argv[argc - 1], O_RDONLY)) == -1)
		ft_print_error(argv[argc - 1]);
	else
	{
		new = ft_get_name(argv[argc - 1], 0, 0, 0);
		ft_get_instructions(fd_r, &(data.parse), &data);
		ft_check_parse(&data);
		if (!(fd_w = open(new, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
			exit(1);
		ft_write_header(fd_w, data);
		ft_printf("Writing output program to %s\n", new);
		ft_free_data(data);
		close(fd_r);
		close(fd_w);
		free(new);
	}
	return (0);
}
