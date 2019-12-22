/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:57:53 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/08 16:57:55 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_link	*crt_link(t_node *href, int is_true, int llink)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		die();
	new->is_true = is_true;
	new->llink = llink;
	new->old = NULL;
	new->node = href;
	new->display = 0;
	new->next = NULL;
	return (new);
}

static	t_node	*crt_node(t_node *parent, t_node *firts, t_main *main)
{
	t_node	*new;

	if (!(new = (t_node*)malloc(sizeof(t_node))))
		die();
	if (!(new->linkbox = (t_rel*)malloc(sizeof(t_rel))))
		die();
	new->linkbox->count = 0;
	new->linkbox->link = crt_link(firts, 1, 0);
	swap_link(firts, parent, new, -1);
	new->linkbox->link->next = crt_link(parent, -1, 0);
	new->distance = MAXINT / 2;
	new->is_known = 0;
	new->is_visit = 0;
	new->copy = NULL;
	new->split = 'I';
	new->id = parent->id;
	new->name = parent->name;
	new->x = parent->x - 10;
	new->y = parent->y - 10;
	parent->x += 10;
	parent->y += 10;
	new->next = main->graph->node;
	return (new);
}

static	void	new_links(t_node *join, t_node *created, int llink)
{
	t_link	*new;

	new = crt_link(created, 1, llink);
	new->next = join->linkbox->link;
	join->linkbox->link = new;
	new = crt_link(join, -1, llink);
	new->next = created->linkbox->link;
	created->linkbox->link = new;
}

static	void	fnorm(t_path *path, t_node *tmp)
{
	t_link	*change;

	change = path->next->node->linkbox->link;
	while (change)
	{
		if (change->node != tmp && change->node != path->node
			&& change->node != path->next->next->node)
		{
			if (!change->is_true)
			{
				swap_link(change->node, path->next->node,
							path->next->node, -1);
				new_links(change->node, tmp, change->llink);
				change->is_true = 1;
			}
		}
		change = change->next;
	}
}

void			split_path(t_main *main)
{
	t_path	*path;
	t_node	*tmp;

	path = main->paths->path;
	while (path->next->next)
	{
		if (!path->next->node->split)
		{
			tmp = crt_node(path->next->node, path->node, main);
			path->next->node->split = 'O';
			swap_link(path->next->node, path->node, tmp, 1);
			if (path->node->split == 'O')
				swap_link(path->node, path->next->node, tmp, -1);
			main->graph->node = tmp;
			fnorm(path, tmp);
		}
		path = path->next;
	}
}
