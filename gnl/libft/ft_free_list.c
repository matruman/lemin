/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matruman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:56:47 by matruman          #+#    #+#             */
/*   Updated: 2020/02/11 13:07:19 by matruman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_free_list(t_list **list)
{
	t_list	*clist;
	t_list	*next;

	if (!list || !(*list))
		return (1);
	clist = *list;
	while (clist)
	{
		next = clist->next;
		free(clist->content);
		free(clist);
		clist = next;
	}
	*list = NULL;
	return (1);
}
