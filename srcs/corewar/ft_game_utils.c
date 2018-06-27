/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 11:27:57 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 12:33:24 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*ft_control_comment(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
		if (str[i] == '\'')
			str[i] = ' ';
	m_pro_null(ret = ft_strjoin(str, "\'"));
	return (ret);
}
