/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:28:47 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/17 20:28:48 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			free_way(t_way ***ways, int count, int *ways_counter)
{
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (ways[i][j])
		{
			free(ways[i][j]);
			++j;
		}
		free(ways[i]);
		++i;
	}
	free(ways_counter);
	free(ways);
}

void			free_graph(t_graph *graph)
{
	t_node	*node;
	t_node	*tmpn;
	t_link	*link;
	t_link	*tmpl;

	node = graph->node;
	while (node)
	{
		link = node->linkbox->link;
		while (link)
		{
			tmpl = link->next;
			free(link);
			link = tmpl;
		}
		free(node->linkbox);
		tmpn = node->next;
		free(node);
		node = tmpn;
	}
	free(graph);
}

void			free_path(t_main *main)
{
	t_paths	*paths;
	t_paths	*tpaths;
	t_path	*path;
	t_path	*tpath;

	paths = main->copy_paths;
	while (paths)
	{
		path = paths->path;
		while (path)
		{
			tpath = path->next;
			free(path);
			path = tpath;
		}
		tpaths = paths->next;
		free(paths);
		paths = tpaths;
	}
	main->copy_paths = NULL;
}
