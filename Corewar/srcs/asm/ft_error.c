/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:35:57 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:35:59 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

void	ft_parse_error(t_parse *parse)
{
	if (!parse)
	{
		ft_putstr_fd("Parse error \" is missing\n", 2);
		exit(1);
	}
	write(2, "Parse error ", 12);
	ft_putstr_fd(parse->label, 2);
	write(2, " [", 2);
	ft_putnbr_fd(parse->lig, 2);
	write(2, "]", 1);
	write(2, "[", 1);
	ft_putnbr_fd(parse->col, 2);
	write(2, "]\n", 2);
	exit(1);
}

void	ft_invalid_arg_error(t_parse *parse)
{
	write(2, "Parse error ", 12);
	ft_putstr_fd(parse->label, 2);
	write(2, " invalid arg number", 19);
	write(2, " [", 2);
	ft_putnbr_fd(parse->lig, 2);
	write(2, "]", 1);
	write(2, "[", 1);
	ft_putnbr_fd(parse->col, 2);
	write(2, "]\n", 2);
	exit(1);
}

void	ft_print_error(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		ft_putstr_fd(" is not a valid file\n", 2);
	}
	else
		ft_putstr_fd("File_name_is_invalid\n", 2);
	exit(1);
}

void	ft_print_usage(char **argv)
{
	write(2, "Usage: ", 7);
	ft_putstr_fd(argv[0], 2);
	write(2, " <sourcefile.s>\n", 16);
	exit(0);
}

void	ft_invalid_label(char *str)
{
	write(2, "Invalid label ", 14);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit(1);
}
