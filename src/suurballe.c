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

#include "../includes/lemin.h"

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
	new->id = node->id;
	new->name = node->name;
	new->x = node->x;
	new->y = node->y;
	new->next = NULL;
	return (new);
}

void 	mark(t_main *main)
{
	t_path	*path;
	t_paths	*paths;
	
	paths = main->paths;
	while (paths)
	{
		path = paths->path;
		while (path)
		{
			if (!path->node->copy)
				path->node->copy = copy_node(path->node);
			path->node = path->node->copy;
			path = path->next;
		}
		paths = paths->next;
	}
}

void	linker(t_main *main)
{
	t_path	*path;
	t_paths	*paths;
	t_link	*link;
	t_link	*relink;

	paths = main->paths;
	while (paths)
	{
		path = paths->path;
		while (path->next)
		{
			link = path->node->linkbox->link;
			while (link)
			{
				if (link->node == path->node->next)
					break ;
				link = link->next;
			}
			if (!link)
			{
				if (!(link = (t_link *)malloc(sizeof(t_link))))
					die();
				link->node = path->next->node;
				link->llink = 1;
				link->is_true = 1;
				link->next = path->node->linkbox->link;
				path->node->linkbox->link = link;
				path->node->linkbox->count += 1;
			}
			link->used = 1;
			relink = path->next->node->linkbox->link;
			while (relink)
			{
				if (relink->node == path->node)
					break ;
				relink = relink->next;
			}
			if (!relink)
			{
				if (!(relink = (t_link *)malloc(sizeof(t_link))))
					die();
				relink->node = path->node;
				relink->llink = 1;
				relink->is_true = -1;
				relink->used = 0;
				relink->next = path->next->node->linkbox->link;
				path->next->node->linkbox->link = relink;
				path->next->node->linkbox->count += 1;
			}
			link->relink = relink;
			relink->relink = link;
			path = path->next;
		}
		paths = paths->next;
	}
}

void		tracer(t_graph *graph)
{
	t_node	*node = graph->node;
	t_link	*here;
	t_link	*there;

	while (node)
	{
		if (node != graph->start && node->linkbox->count > 2)
		{
			here = node->linkbox->link;
			while (here)
			{
				there = here->node->linkbox->link;
				while (here->node->linkbox->count > 2 && there)
				{
					if (there->node == node && (here->used && there->used) && (there->is_true = -2)
					&& (here->is_true = -2) && (here->node->linkbox->count--)
					&& (there->node->linkbox->count--))
						break;
					there = there->next;
				}
				here = here->next;
			}
		}
		node = node->next;
	}
}

void		unsplit_graph(t_graph *graph)
{
	t_node		*node;
	t_node		*check;
	t_link		*clink;
	t_link		*nlink;

	check = graph->node;
	while (check->next)
	{
		node = check->next;
		while (node)
		{
			printf("check: name = %s id = %d\n node: name = %s id = %d\n\n", check->name, check->id, node->name, node->id);
			if (check->id == node->id)
			{
				clink = check->linkbox->link;
				nlink = node->linkbox->link;
				while (clink)
				{
					clink->relink->node = node;
					clink = clink->next;
				}
				check->linkbox->link = NULL;
				while (nlink->next)
					nlink = nlink->next;
				nlink->next = clink;
			}
			node = node->next;
		}
		check = check->next;
	}
}

t_graph		*merge_paths(t_main *main)
{
	t_graph		*graph;
	t_node		*node;

p();
	if (!(graph = (t_graph *)malloc(sizeof(t_graph))))
		die();
	graph->node = NULL;
	node = main->graph->node;
	mark(main);
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
	linker(main);
	printf("after linker\n");
	unsplit_graph(graph);
	printf("after us\n");
	//tracer(graph);
	return (graph);
}
