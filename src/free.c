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

void			free_way(t_way ***ways, int count)
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
