/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:13:58 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/15 21:13:59 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_node	*get_node(t_node *start)
{
	t_link	*tmp;

	tmp = start->linkbox->link;
	while (tmp)
	{
		if (tmp->is_true == 1)
		{
			tmp->is_true = -1;
			tmp->coming = 1;
			return (tmp->node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static	int		counter(t_graph *graph, t_main *main)
{
	t_link	*link;
	t_node	*tmp;
	int		count;

	count = 1;
	tmp = main->waybox->start;
	if (!(tmp = get_node(tmp)))
		return (0);
	while ((tmp = get_node(tmp)))
		++count;
	return (count);
}

static	t_way	*get_struct(t_node **here)
{
	t_node	*node;
	t_link	*link;
	t_way	*new;

	node = *here;
	link = node->linkbox->link;
	while (link)
	{
		if (link->coming)
		{
			link->coming = 0;
			*here = link->node;
			if (!(new = (t_way*)malloc(sizeof(t_way))))
				die();
			new->name = link->node->name;
			new->ant = 0;
			return (new);
		}
		link = link->next;
	}
	return (NULL);
}

static	int		ways_count(t_main *main, t_graph *graph)
{
	t_node	*tmp;
	t_link	*link;
	int		count;

	count = 0;
	tmp = graph->node;
	while (tmp)
	{
		if (tmp->id ==  main->graph->start->id)
		{
			main->waybox->start = tmp;
			link = tmp->linkbox->link;
			while (link)
			{
				if (link->is_true)
					++count;
				link = link->next;
			}
			return (count);
		}
		tmp = tmp->next;
	}
	return (0);
}

static	void	set_result(t_way ***ways, int count, int score, t_main *main)
{
	if (!main->waybox->first)
	{
		main->waybox->first = ways;
		main->waybox->f_count = count;
		main->waybox->f_score = score;
		return ;
	}
	if (main->waybox->second)
		free_way(main->waybox->second, main->waybox->s_count);
	main->waybox->second = main->waybox->first;
	main->waybox->s_count = main->waybox->f_count;
	main->waybox->s_score = main->waybox->f_score;
	main->waybox->first = ways;
	main->waybox->f_count = count;
	main->waybox->f_score = score;
}

int			search_ways(t_main *main, t_graph *graph)
{
	t_way	***way;
	t_node	*tmp;
	int		ways_len;
	int		final;
	int		count;
	int		i;
	int		j;

	if (!(ways_len = ways_count(main, graph)))
		return (0);
	if (!(way = (t_way***)malloc((sizeof(void*) + ways_len) * sizeof(void*))))
		die();
	j = 0;
	final = 0;
	while ((count = counter(graph, main)))
	{
		if (!(way[j] = (t_way**)malloc((sizeof(void*) + count) * sizeof(void*))))
			die();
		i = 0;
		final += count;
		tmp = main->waybox->start;
		while (i < count)
			way[j][i++] = get_struct(&tmp);
		way[j][i] = NULL;
		++j;
	}
	way[j] = NULL;
//	free_graph(graph);
	set_result(way, j, final, main);
	return (j);
}
