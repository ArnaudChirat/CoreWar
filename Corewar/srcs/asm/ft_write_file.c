/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:36:49 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:36:51 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

void	ft_write_header(int fd_w, t_data data)
{
	char tmp[4];

	tmp[0] = (char)(COREWAR_EXEC_MAGIC >> 24 & 0xFF);
	tmp[1] = (char)(COREWAR_EXEC_MAGIC >> 16 & 0xFF);
	tmp[2] = (char)(COREWAR_EXEC_MAGIC >> 8 & 0xFF);
	tmp[3] = (char)(COREWAR_EXEC_MAGIC & 0xFF);
	write(fd_w, tmp, 4);
	write(fd_w, data.header.prog_name, PROG_NAME_LENGTH + 4);
	tmp[0] = (char)(data.len >> 24 & 0xFF);
	tmp[1] = (char)(data.len >> 16 & 0xFF);
	tmp[2] = (char)(data.len >> 8 & 0xFF);
	tmp[3] = (char)(data.len & 0xFF);
	write(fd_w, tmp, 4);
	write(fd_w, data.header.comment, COMMENT_LENGTH + 4);
	write(fd_w, data.bytecode, data.len);
}
