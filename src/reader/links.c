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

static	void	push_links_norm(t_links *tmp, t_links *new)
{
	while (tmp->next)
	{
		if (tmp->relation == new->relation)
			die();
		tmp = tmp->next;
	}
	if (tmp->relation == new->relation)
		die();
	tmp->next = new; 
}

static	void	push_links(t_main *main, int where, int relation)
{
	t_links	*new;

	if (!(new = (t_links*)malloc(sizeof(t_links))))
		die();
	new->relation = relation;
	new->next = NULL;
	main->graph->info[where]->count += 1;
	if (!main->graph->info[where]->links)
	{
		main->graph->info[where]->links = new;
		return ;
	}
	push_links_norm(main->graph->info[where]->links, new);
}

int				reader_is_link(t_main *main, char *line)
{
	char	*tmp;
	int		firts;
	int		second;

	if (!main->reader->flag)
		graph_init(main);
	firts = ft_atoi(line);
	if (!(tmp = ft_strchr(line, '-')))
		return (0);
	tmp += 1;
	second = ft_atoi(tmp);
	if (second >= main->rooms || firts >= main->rooms)
		die();
	push_links(main, firts, second);
	push_links(main, second, firts);
	main->links += 2;
	return (1);
}
