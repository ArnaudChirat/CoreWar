/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:02:01 by achirat           #+#    #+#             */
/*   Updated: 2018/01/25 21:54:23 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (!new)
		return ;
	if (!tmp)
	{
		new->next = NULL;
		*alst = new;
	}
	else
	{
		while (alst && tmp->next)
			tmp = tmp->next;
		new->next = NULL;
		tmp->next = new;
	}
}
