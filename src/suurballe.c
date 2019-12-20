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
	new->split = node->split;
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
	t_link	*link;
	
	paths = main->copy_paths;
	while (paths)
	{
		path = paths->path;
		while (path)
		{
			if (path->node->split == 'I')
			{
				link = path->node->linkbox->link;
				while (link->node->id != path->node->id && link->node->split == 'O')
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

void	linker(t_main *main)
{
	t_path	*path;
	t_paths	*paths;
	t_link	*link;
	t_link	*relink;

	paths = main->copy_paths;
	while (paths)
	{
		path = paths->path;
		while (path->next)
		{
			link = path->node->linkbox->link;
			while (link)
			{
				if (link->node == path->next->node)
					break ;
				link = link->next;
			}
			if (!link)
			{
				if (!(link = (t_link *)malloc(sizeof(t_link))))
					die();
				link->node = path->next->node;
				link->llink = 1;
				link->coming = 0;
				link->used = 0;
				link->next = path->node->linkbox->link;
				path->node->linkbox->link = link;
				path->node->linkbox->count += 1;
			}
			link->is_true = 1;
			link->used += 1;
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
				link->coming = 0;
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

// void		unsplit_graph(t_graph *graph)
// {
// 	t_node		*node;
// 	t_node		*check;
// 	t_link		*clink;
// 	t_link		*nlink;
// 	t_link		*n2link;

// 	check = graph->node;
// 	while (check->next)
// 	{
// 		node = check->next;
// 		while (node)
// 		{
// 			printf("check: name = %s id = %d\n node: name = %s id = %d\n\n", check->name, check->id, node->name, node->id);
// 			if (check->id == node->id)
// 			{
// 				clink = check->linkbox->link;
// 				nlink = node->linkbox->link;
// 				while (clink)
// 				{
// 					n2link = node->linkbox->link;
// 					while (n2link)
// 					{
// 						if (n2link->node == clink->node)
// 						{

// 							n2link->relink->is_true = -2;
// 						}
// 						n2link = n2link->next;
// 					}
// 					clink->relink->node = node;
// 					clink = clink->next;
// 				}	
// 				while (nlink->next)
// 					nlink = nlink->next;
// 				nlink->next = check->linkbox->link;
// 				check->linkbox->link = NULL;
// 			}
// 			node = node->next;
// 		}
// 		check = check->next;
// 	}
// }

// void		unsplit_graph(t_graph *graph)
// {
// 	t_node		*node;
// 	t_node		*check;

// 	check = graph->node;
// 	while (check->next)
// 	{
// 		node = check->next;
// 		while (node)
// 		{
// 			printf("check: name = %s id = %d\n node: name = %s id = %d\n\n", check->name, check->id, node->name, node->id);
// 			if (check->id == node->id)
// 			{
// 				if (check->split == 'I')
// 					check->out = node;
// 				else
// 					node->out = check;
// 			}
// 			node = node->next;
// 		}
// 		check = check->next;
// 	}
// }

static	t_paths	*copy_paths(t_paths *paths, t_main *main)
{
    t_paths *parent;

    if (!(parent = (t_paths*)malloc(sizeof(t_paths))))
        die();
    parent->s_len = paths->s_len;
    parent->n_len = paths->n_len;
    parent->path = NULL;
    parent->next = NULL;
	parent->last = NULL;
	if (!main->copy_paths)
	{
		main->copy_paths = parent;
		main->copy_last = parent;
		return (parent);
	}
	main->copy_last->next = parent;
	main->copy_last = parent;
	return (parent);
}

static	void	copy_path(t_path *path, t_paths *parent)
{
    t_path  *new;

    if (!(new = (t_path*)malloc(sizeof(t_path))))
        die();
    new->node = path->node;
    new->score = path->score;
    new->next = NULL;
    if (!parent->path)
	{
		parent->path = new;
		parent->last = new;
		return ;
	}
	parent->last->next = new;
	parent->last = new;
}

void			cp_paths(t_main *main)
{
	t_paths	*paths;
	t_paths	*c_paths;
	t_path	*path;

	paths = main->paths;
	while (paths)
	{
		c_paths = copy_paths(paths, main);
		path = paths->path;
		while (path)
		{
			copy_path(path, c_paths);
			path = path->next;
		}
		paths = paths->next;
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
	main->copy_paths = NULL;
	cp_paths(main);
	mark(main);
// <----------------------------------------------------------- FREEEEEEEEEEEEEE
		// t_paths *a1;
		// t_path *a2;

		// a1 = main->copy_paths;
		// while (a1)
		// {
		// 	printf("\n\n");
		// 	a2 = a1->path;
		// 	while (a2)
		// 	{
		// 		printf("%s-%c  \n", a2->node->name, a2->node->split);
		// 		a2 = a2->next;
		// 	}
		// 	printf("\n\n");
		// 	a1 = a1->next;
		// }

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
	// printf("after linker\n");
	tracer(graph);
		// t_node *a1;
		// t_link *a2;

		// a1 = graph->node;
		// while (a1)
		// {
		// 	printf("%s%c: ", a1->name, a1->split);
		// 	a2 = a1->linkbox->link;
		// 	while (a2)
		// 	{
		// 		printf(">%s%c %d %d< ", a2->node->name, a2->node->split, a2->is_true, a2->used);
		// 		a2 = a2->next;
		// 	}
		// 	printf("\n\n");
		// 	a1 = a1->next;
		// }
	return (graph);
}
