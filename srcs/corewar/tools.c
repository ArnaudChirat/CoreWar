/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:52:12 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 16:52:16 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Un echantillons de messages d'erreur possible appeles dans plusieurs
**	fonctions du programme en fonction du code passe en parametre
*/

static void			ft_error2(int error_code, char *msg, int v1, int v2)
{
	if (error_code == 4)
	{
		ft_putstr_fd("Error: File ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" has too large a code (", 2);
		ft_putnbr_fd(v1, 2);
		ft_putstr_fd(" bytes > ", 2);
		ft_putnbr_fd(v2, 2);
		ft_putstr_fd(" bytes)", 2);
	}
	else if (error_code == 5)
		ft_putstr_fd("Error: name or comment doesn't respect header rules", 2);
	else if (error_code == 6)
	{
		ft_putstr_fd("Error: File ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" has a code size that differ from what its header says",
				2);
	}
	else if (error_code == 7)
	{
		ft_printf("Champion %s won without a fight ! ", msg);
		ft_printf("BOOOOOoooooooorrrrrriiinngggggg....");
	}
}

void				ft_error(int error_code, char *msg, int v1, int v2)
{
	if (error_code == 0)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	else if (error_code == 1)
		ft_putstr_fd(msg, 2);
	else if (error_code == 2)
	{
		ft_putstr_fd("Can't read source file ", 2);
		if (msg)
			ft_putstr_fd(msg, 2);
		ft_error_usage("\nPlease control your right use of the program\n");
	}
	else if (error_code == 3)
	{
		ft_putstr_fd("Error: File ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" is too small to be a champion", 2);
	}
	else
		ft_error2(error_code, msg, v1, v2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

/*
**	L'usage du programme est lue dans un fichier externe a partir de cette
**	fonction.
*/

void				ft_error_usage(char *msg)
{
	int		fd;
	char	buffer[500];
	int		i;

	ft_bzero(buffer, 500);
	fd = open("./srcs/corewar/usage.txt", O_RDONLY);
	if ((i = read(fd, buffer, 500)) == -1)
		ft_error(0, "Read failled in ft_error_usage\n", 0, 0);
	buffer[i] = '\0';
	if (msg)
		ft_putstr_fd(msg, 2);
	write(2, "\n", 1);
	ft_putstr_fd(buffer, 2);
	write(2, "\n", 1);
	close(fd);
	exit(EXIT_FAILURE);
}

/*
**	Fonction de parsing du champion, elle retourne la partie non nulle
**	trouvee dans le troncon demande
*/

char				*ft_cut_read(char *s, int start, int len)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	j = 0;
	size = 0;
	i = start;
	while (i < start + len)
		if (s[i++] != 0)
			size++;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		ft_error(0, "Malloc failed in ft_cut_read (char *line)", 0, 0);
	i = start;
	while (j < size)
	{
		if (s[i] != 0)
			str[j++] = s[i++];
		else
			i++;
	}
	str[j] = '\0';
	return (str);
}

/*
**	Convertit une chaine de 4 caracteres en un int
*/

unsigned int		ft_convert_int_base(char *str)
{
	int				size;
	unsigned int	result;

	size = 0;
	result = 0;
	while (size < 4)
	{
		if (!str[size])
			break ;
		result = result * 16 * 16;
		result += str[size] & 0xff;
		size++;
	}
	ft_strdel(&str);
	return (result);
}
