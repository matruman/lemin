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

void			clean_flags(t_main *main)
{
	t_node	*node;

	node = main->graph->node;
	while (node)
	{
		node->distance = MAXINT / 2;
		node->is_known = 0;
		node->is_visit = 0;
		node = node->next;
	}
}

void			reverse_link(t_node *node, t_link *link)
{
	t_link	*tmp;

	link->is_true = 1;
	link->llink = 0;
	tmp = link->node->linkbox->link;
	while (tmp)
	{
		if (tmp->node == node)
		{
			tmp->llink = 0;
			tmp->is_true = -1;
			return ;
		}
		tmp = tmp->next;
	}
}

void			swap_link(t_node *sch, t_node *needle,
							t_node *swap, int f)
{
	t_link	*tmp;

	tmp = sch->linkbox->link;
	while (tmp)
	{
		if (tmp->node == needle)
		{
			tmp->old = tmp->node;
			tmp->is_true = f;
			tmp->node = swap;
			return ;
		}
		tmp = tmp->next;
	}
}

int				is_set(t_main *main, t_link *link)
{
	t_path	*path;

	path = main->paths->path;
	while (path)
	{
		if (path->node == link->node)
		{
			return (1);
		}
		path = path->next;
	}
	return (0);
}

int				min_int(int first, int second)
{
	return (first > second ? second : first);
}
