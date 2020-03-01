/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:28:55 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/07 16:28:56 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	void	write_items(int *min, t_link **needle, t_link *point, int f)
{
	if (!f)
	{
		*min = MAXINT;
		(*needle) = NULL;
		return ;
	}
	*min = point->node->distance;
	(*needle) = point;
}

static	int		cl_memory(t_main *main)
{
	t_path	*path;
	t_path	*tmp;
	t_paths	*temp;

	path = main->paths->path;
	while (path)
	{
		tmp = path->next;
		free(path);
		path = tmp;
	}
	temp = main->paths->next;
	free(main->paths);
	main->paths = temp;
	return (0);
}

static	void	crt_parent(t_main *main)
{
	t_paths *parent;

	if (!(parent = (t_paths*)malloc(sizeof(t_paths))))
		die();
	parent->s_len = 0;
	parent->n_len = 0;
	parent->path = NULL;
	parent->next = NULL;
	parent->last = NULL;
	if (!main->paths)
	{
		main->paths = parent;
		return ;
	}
	parent->next = main->paths;
	main->paths = parent;
}

static	void	crt_path(t_main *main, t_node *node, t_link *need)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		die();
	if (!main->paths->path)
		main->paths->s_len = node->distance;
	main->paths->n_len += 1;
	path->node = node;
	path->score = need->llink;
	path->next = main->paths->path;
	main->paths->path = path;
	if (node != main->graph->start)
		reverse_link(node, need);
}

int				get_path(t_main *main, int i)
{
	t_node	*node;
	t_link	*needle;
	t_link	*link;
	int		min;

	crt_parent(main);
	node = main->graph->end;
	while (node != main->graph->start && ++i)
	{
		link = node->linkbox->link;
		write_items(&min, &needle, link, 0);
		while (link)
		{
			if (min > link->node->distance && link->is_true <= 0
				&& !is_set(main, link))
				write_items(&min, &needle, link, 1);
			link = link->next;
		}
		if (!needle || i > main->rooms)
			return (cl_memory(main));
		crt_path(main, node, needle);
		node = needle->node;
	}
	crt_path(main, node, needle);
	return (1);
}
