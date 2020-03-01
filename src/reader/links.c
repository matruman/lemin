/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:23:12 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/01 21:23:14 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	void	push_link_norm(t_node *parent, t_link *new)
{
	t_link	*tmp;

	tmp = parent->linkbox->link;
	while (tmp->next)
	{
		if (tmp->node == new->node)
			die();
		tmp = tmp->next;
	}
	if (tmp->node == new->node)
		die();
	tmp->next = new;
}

static	t_link	*push_link(t_node *parent,
	t_node *href)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		die();
	new->is_true = 0;
	new->llink = 1;
	new->old = NULL;
	new->display = 0;
	new->node = href;
	new->none = 0;
	new->next = NULL;
	if (!parent->linkbox->link)
	{
		parent->linkbox->link = new;
		return (new);
	}
	push_link_norm(parent, new);
	return (new);
}

static	void	node_search(t_main *main, char *str1, char *str2)
{
	t_node	*first;
	t_node	*second;
	t_node	*tmp;
	t_link	*new;

	tmp = main->graph->node;
	first = NULL;
	second = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, str1))
			first = tmp;
		if (!ft_strcmp(tmp->name, str2))
			second = tmp;
		tmp = tmp->next;
	}
	if (!first || !second)
		die();
	new = push_link(first, second);
	new->relink = push_link(second, first);
	new->relink->relink = new;
	first->linkbox->count += 1;
	second->linkbox->count += 1;
}

void			reader_crtlink(t_main *main, char **items, char *line)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!items || lm_count(items) != 2)
		die();
	while (i < 2)
	{
		len += ft_strlen(items[i]);
		++i;
	}
	if (ft_strlen(line) - len > 1)
		die();
	node_search(main, items[0], items[1]);
	main->links += 2;
	cleaner_2_array(items, 2);
}
