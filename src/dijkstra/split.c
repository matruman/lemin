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

static	void	swap_link(t_node *sch, t_node *needle, t_node *swap, int f)
{
	t_link	*tmp;

	tmp = sch->linkbox->link;
	while (tmp)
	{
		if (tmp->node == needle)
		{
			tmp->old = tmp->node;
			tmp->is_true = f;
			tmp->node = swap;
		}
		tmp = tmp->next;
	}
}

static	t_link	*crt_link(t_node *href)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		die();
	new->is_true = 1;
	new->llink = 1;
	new->old = NULL;
	new->node = href;
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
	new->linkbox->link = crt_link(firts);
	new->distance = MAXINT / 2;
	new->is_known = 0;
	new->is_visit = 0;
	new->split = 'I';
	new->name = parent->name;
	new->x = parent->x - 10;
	new->y = parent->y - 10;
	parent->x += 10;
	parent->y += 10;
	new->next = main->graph->node;
	return (new);
}

static	void	set_none(t_node *where, t_node *needle)
{
	t_link	*tmp;

	tmp = where->linkbox->link;
	while (tmp)
	{
		if (tmp->node == needle)
		{
			tmp->none = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void            split_path(t_main *main)
{
    t_path  *path;
	t_node	*tmp;
	t_link	*change;

    path = main->paths->path;
    while (path->next->next)
    {
		tmp = crt_node(path->next->node, path->node, main);
		path->next->node->split = 'O';
		swap_link(path->next->node, path->node, tmp, 1);
		set_none(path->node, path->next->node);
		main->graph->node = tmp;
		change = path->next->node->linkbox->link;
		while (change)
		{
			if (change->node != tmp && change->node != path->node
				&& change->node != path->next->next->node)
			{
				swap_link(change->node, path->next->node, tmp, 1);
				change->is_true = 1;
			}
			change = change->next;
		}

			// t_node *a1;
			// t_link *a2;

			// a1 = main->graph->node;
			// while (a1)
			// {
			// 	printf("%s%c: ", a1->name, a1->split);
			// 	a2 = a1->linkbox->link;
			// 	while (a2)
			// 	{
			// 		printf("%s%c ", a2->node->name, a2->node->split);
			// 		a2 = a2->next;
			// 	}
			// 	printf("\n\n");
			// 	a1 = a1->next;
			// }
			// display_graph(main->graph);
			// exit(0);
		path = path->next;
		
    }
}
