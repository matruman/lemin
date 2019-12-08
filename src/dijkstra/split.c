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

static	void	swap_link(t_node *node, t_node *need, t_node *swap, int f)
{
	t_link	*tmp;

	tmp = node->linkbox->link;
	while (tmp)
	{
		if (tmp->node == need)
		{
			tmp->node = swap;
			tmp->is_true = f;
			return ;
		}
		tmp = tmp->next;
	}
}

static	t_link	*crt_link(t_node *path)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		die();
	new->is_true = -1;
	new->llink = 1;
	new->node = path;
	new->next = NULL;
	return (new);
}

static	t_node	*duplicate(t_node *node, t_node *path)
{
	t_node	*new;

	if (!(new = (t_node*)malloc(sizeof(t_node))))
		die();
	if (!(new->linkbox = (t_rel*)malloc(sizeof(t_rel))))
		die();
	new->linkbox->count = 1;
	new->linkbox->link = crt_link(path);
	new->distance = MAXINT / 2;
	new->is_known = 0;
	new->is_visit = 0;
	new->split = 'I';
	new->name = node->name;
	new->x = node->x - 10;
	new->y = node->y - 100;
	new->id = node->id;
	new->next = node->next;
	return (new);
}

static	void	final_swap(t_main *main, t_link *link, t_node *here)
{
	t_link	*tmp;

// printf("%s %c\n", here->next->name, here->next->split);
// die();
	tmp = link->node->linkbox->link;
	while (tmp)
	{
		if (tmp->node == here)
		{
			tmp->node = here->next;
			tmp->is_true = -1;
			return ;
		}
		tmp = tmp->next;
	}
}

void            split_path(t_main *main)
{
    t_path  *path;
	t_link	*tmp;

    path = main->paths->path;
    while (path->next->next)
    {
		if (!path->next->node->split)
		{
			path->next->node->next = duplicate(path->next->node, path->next->next->node);
			path->next->node->split = 'O';
			swap_link(path->next->node, path->next->next->node, path->next->node->next, -1);
			tmp = path->next->node->linkbox->link;
			while (tmp)
			{
				if (tmp->node != path->node && tmp->node != path->next->node->next)
				{
					final_swap(main, tmp, path->next->node);
					tmp->is_true = -1;
				}
				tmp = tmp->next;
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
		display_graph(main->graph);
		exit(0);
        path = path->next;
    }
}
