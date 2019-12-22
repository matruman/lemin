/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matruman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:47:20 by matruman          #+#    #+#             */
/*   Updated: 2019/12/22 17:47:22 by matruman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

t_node		*copy_node(t_node *node)
{
	t_node		*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))) ||
	!(new->linkbox = (t_rel*)malloc(sizeof(t_rel))))
		die();
	new->linkbox->count = 0;
	new->linkbox->link = NULL;
	new->distance = MAXINT / 2;
	new->is_known = 0;
	new->is_visit = 0;
	new->split = node->split;
	new->id = node->id;
	new->name = node->name;
	new->x = node->x;
	new->y = node->y;
	new->next = NULL;
	return (new);
}

void		mark(t_main *main, t_path *path, t_paths *paths, t_link *link)
{
	paths = main->copy_paths;
	while (paths)
	{
		path = paths->path;
		while (path)
		{
			if (path->node->split == 'I')
			{
				link = path->node->linkbox->link;
				while (link->node->id != path->node->id &&
				link->node->split == 'O')
					link = link->next;
				path->node = link->node;
			}
			if (!path->node->copy)
				path->node->copy = copy_node(path->node);
			path->node = path->node->copy;
			path = path->next;
		}
		paths = paths->next;
	}
}
