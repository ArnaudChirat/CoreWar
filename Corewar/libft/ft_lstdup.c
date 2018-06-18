/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:13:04 by achirat           #+#    #+#             */
/*   Updated: 2018/01/25 22:23:13 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *list)
{
	t_list	*alst_new;
	t_list	*new;

	if (!list)
		return (0);
	alst_new = NULL;
	while (list)
	{
		new = NULL;
		new = ft_lstnew(list->content, list->content_size);
		ft_lstaddend(&alst_new, new);
		list = list->next;
	}
	return (alst_new);
}
