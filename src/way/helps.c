/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:36:51 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/22 17:36:52 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

int				ways_count(t_main *main, t_graph *graph)
{
	t_node	*tmp;
	t_link	*link;
	int		count;

	count = 0;
	tmp = graph->node;
	while (tmp)
	{
		if (tmp->id == main->graph->start->id)
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

void			set_result(t_way ***ways, int count,
							t_main *main, int *way_counter)
{
	int		score;

	score = main->waybox->tmp;
	if (!main->waybox->first)
	{
		main->waybox->first = ways;
		main->waybox->f_count = count;
		main->waybox->f_score = score;
		main->waybox->count_first = way_counter;
		return ;
	}
	if (main->waybox->second)
		free_way(main->waybox->second, main->waybox->s_count,
					main->waybox->count_second);
	main->waybox->count_second = main->waybox->count_first;
	main->waybox->second = main->waybox->first;
	main->waybox->s_count = main->waybox->f_count;
	main->waybox->s_score = main->waybox->f_score;
	main->waybox->first = ways;
	main->waybox->count_first = way_counter;
	main->waybox->f_count = count;
	main->waybox->f_score = score;
}

int				counter(t_way **item)
{
	int		i;

	i = 0;
	while (item[i])
		++i;
	return (i);
}
