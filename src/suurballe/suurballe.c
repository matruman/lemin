/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matruman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:58:18 by matruman          #+#    #+#             */
/*   Updated: 2019/12/08 16:58:20 by matruman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

void		create_link(t_link **link, t_path *path)
{
	if (!(*link = (t_link *)malloc(sizeof(t_link))))
		die();
	(*link)->node = path->next->node;
	(*link)->llink = 1;
	(*link)->coming = 0;
	(*link)->used = 0;
	(*link)->next = path->node->linkbox->link;
	path->node->linkbox->link = *link;
	path->node->linkbox->count += 1;
}

void		create_relink(t_link **relink, t_path *path)
{
	if (!(*relink = (t_link *)malloc(sizeof(t_link))))
		die();
	(*relink)->node = path->node;
	(*relink)->llink = 1;
	(*relink)->is_true = -1;
	(*relink)->used = 0;
	(*relink)->coming = 0;
	(*relink)->next = path->next->node->linkbox->link;
	path->next->node->linkbox->link = *relink;
	path->next->node->linkbox->count += 1;
}

void		linker(t_paths *paths, t_path *path, t_link *link, t_link *relink)
{
	while (paths)
	{
		path = paths->path;
		while (path->next)
		{
			link = path->node->linkbox->link;
			while (link && link->node != path->next->node)
				link = link->next;
			if (!link)
				create_link(&link, path);
			link->is_true = 1;
			link->used += 1;
			relink = path->next->node->linkbox->link;
			while (relink && relink->node != path->node)
				relink = relink->next;
			if (!relink)
				create_relink(&relink, path);
			link->relink = relink;
			relink->relink = link;
			path = path->next;
		}
		paths = paths->next;
	}
}

void		tracer(t_graph *graph)
{
	t_node *node;
	t_link *link;

	node = graph->node;
	while (node)
	{
		link = node->linkbox->link;
		while (link)
		{
			if (link->is_true == 1 && link->relink->is_true == 1)
			{
				if (!(link->used - link->relink->used))
				{
					link->is_true = -2;
					link->relink->is_true = -2;
				}
				else
					(link->used > link->relink->used) ?
					(link->relink->is_true = -2) :
					(link->is_true = -2);
			}
			link = link->next;
		}
		node = node->next;
	}
}

t_graph		*merge_paths(t_main *main)
{
	t_graph		*graph;
	t_node		*node;

	if (!(graph = (t_graph *)malloc(sizeof(t_graph))))
		die();
	graph->node = NULL;
	node = main->graph->node;
	cp_paths(main);
	mark(main, 0, 0, 0);
	graph->start = main->graph->start->copy;
	graph->end = main->graph->end->copy;
	while (node)
	{
		if (node->copy)
		{
			node->copy->next = graph->node;
			graph->node = node->copy;
			node->copy = NULL;
		}
		node = node->next;
	}
	linker(main->copy_paths, 0, 0, 0);
	tracer(graph);
	free_path(main->copy_paths);
	return (graph);
}
