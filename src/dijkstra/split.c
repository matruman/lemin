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
			return ;
		}
		tmp = tmp->next;
	}
}

static	t_link	*crt_link(t_node *href, int is_true)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		die();
	new->is_true = is_true;
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
	new->linkbox->link = crt_link(firts, 1);
	swap_link(firts, parent, new, -1);
	new->linkbox->link->next = crt_link(parent, -1);
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

static	void	new_links(t_node *join, t_node *created)
{
	t_link	*new;

	new = crt_link(created, 1);
	new->next = join->linkbox->link;
	join->linkbox->link = new;
	new = crt_link(join, -1);
	new->next = created->linkbox->link;
	created->linkbox->link = new;
}

static	void	rechange_link(t_link *srh, t_node *from, t_node *into)
{
	t_link	*tmp;
	t_link	*swap;

	tmp = from->linkbox->link;
	while (tmp)
	{
		if (tmp->next == srh)
		{
			swap = tmp->next;
			tmp->next = tmp->next->next;
			swap->next = into->linkbox->link;
			into->linkbox->link = swap;
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
		if (!path->next->node->split)
		{
			tmp = crt_node(path->next->node, path->node, main);
			path->next->node->split = 'O';
			swap_link(path->next->node, path->node, tmp, 1);
			if (path->node->split == 'O')
				swap_link(path->node, path->next->node, tmp, -1);
			main->graph->node = tmp;
			change = path->next->node->linkbox->link;
			while (change)
			{
				if (change->node != tmp && change->node != path->node //----------------------------------------------------------
					&& change->node != path->next->next->node)
				{
					if (change->is_true == -1)
					{
						swap_link(change->node, path->next->node, tmp, 1);
						rechange_link(change, path->next->node, tmp);
					}
					else if (!change->is_true)
					{
						swap_link(change->node, path->next->node, path->next->node, -1);
						new_links(change->node, tmp);
						change->is_true = 1;
					}
				}
				change = change->next;
			}
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
		//	display_graph(main->graph);
			// exit(0);
		path = path->next;
    }
}
