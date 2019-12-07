/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:55:18 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/07 18:55:19 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

void            reverse_link(t_node *node, t_link *link)
{
	t_link  *tmp;

	link->is_true = 1;
	tmp = link->node->linkbox->link;
	while (tmp)
	{
		if (tmp->node == node)
		{
			tmp->is_true = -1; 
			return ;
		}
		tmp = tmp->next;
	}
}