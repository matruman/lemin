/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:16:23 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/05 18:16:25 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_known	*min_stack(t_main *main)
{
	t_known	*tmp;
	t_known	*res;

	if (main->known == NULL)
		return (NULL);
	res = main->known;
	tmp = main->known;
	while (tmp)
	{
		if (tmp->node->distance < res->node->distance)
		{
			res = tmp;
		}
		tmp = tmp->next;
	}
	return (res);
}

void			del_from_stack(t_main *main, t_known *elem)
{
	t_known		*prev;
	t_known		*next;

	prev = elem->prev;
	next = elem->next;
	if (prev)
		prev->next = next;
	else
		main->known = next;
	if (next)
		next->prev = prev;
	ft_memdel((void**)&elem);
}

static	void	push_to_start(t_main *main, t_node *node, int len)
{
	t_known	*stack;
	t_known	*tmp;

	if (!(stack = (t_known*)malloc(sizeof(t_known))))
		die();
	stack->node = node;
	stack->node->distance = len;
	tmp = main->known;
	main->known->prev = stack;
	main->known = stack;
	stack->prev = NULL;
	stack->next = tmp;
}

static	void	run(t_main *main)
{
	t_known	*stack;
	t_link	*tmp;

	while ((stack = min_stack(main)))
	{
		tmp = stack->node->linkbox->link;
		while (tmp)
		{
			if (tmp->is_true >= 0 && !tmp->node->is_known)
			{
				push_to_start(main, tmp->node, min_int(tmp->llink +
				stack->node->distance, tmp->node->distance));
				tmp->node->is_known = 1;
			}
			else if (tmp->is_true >= 0 && !tmp->node->is_visit)
				tmp->node->distance = min_int(tmp->llink +
				stack->node->distance, tmp->node->distance);
			tmp = tmp->next;
		}
		stack->node->is_visit = 1;
		del_from_stack(main, stack);
	}
}

int				dijkstra(t_main *main)
{
	t_known	*stack;

	if (!(stack = (t_known*)malloc(sizeof(t_known))))
		die();
	stack->node = main->graph->start;
	stack->node->is_known = 1;
	stack->node->distance = 0;
	stack->node->is_visit = 1;
	stack->prev = NULL;
	stack->next = NULL;
	main->known = stack;
	run(main);
	if (!get_path(main, 0))
	{
		clean_flags(main);
		return (0);
	}
	if (!main->waybox->first)
		search_ways(main, merge_paths(main));
	clean_flags(main);
	split_path(main);
	return (1);
}
