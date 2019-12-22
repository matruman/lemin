/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:28:48 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/01 19:28:50 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

void			reader_words(t_main *main, char **line, int ch)
{
	if (!ft_strcmp(*line, "##start") && !main->graph->start)
	{
		output_write(main, *line, 1);
		ft_memdel((void**)line);
		get_next_line(ch, line);
		reader_crtroom(main, ft_strsplit(*line, ' '), 'S');
		return ;
	}
	else if (!ft_strcmp(*line, "##end") && !main->graph->end)
	{
		output_write(main, *line, 1);
		ft_memdel((void**)line);
		get_next_line(ch, line);
		reader_crtroom(main, ft_strsplit(*line, ' '), 'E');
		return ;
	}
	die();
}

static	void	push_room(t_main *main, t_node *new)
{
	t_node	*tmp;

	main->rooms += 1;
	if (!main->graph->node)
	{
		new->id = 1;
		main->graph->node = new;
		return ;
	}
	tmp = main->graph->node;
	while (tmp->next)
	{
		if ((tmp->x == new->x && tmp->y == new->y)
			|| !ft_strcmp(tmp->name, new->name))
			die();
		tmp = tmp->next;
	}
	if ((tmp->x == new->x && tmp->y == new->y)
		|| !ft_strcmp(tmp->name, new->name))
		die();
	new->id = tmp->id + 1;
	tmp->next = new;
}

void			reader_crtroom(t_main *main, char **items, char flag)
{
	t_node	*new;

	if (!items || lm_count(items) != 3)
		die();
	if (!(new = (t_node*)malloc(sizeof(t_node))))
		die();
	if (!(new->linkbox = (t_rel*)malloc(sizeof(t_rel))))
		die();
	new->linkbox->count = 0;
	new->linkbox->link = NULL;
	new->distance = MAXINT / 2;
	new->is_known = 0;
	new->is_visit = 0;
	new->split = 0;
	new->name = ft_strdup(items[0]);
	new->x = die_atoi(items[1]);
	new->y = die_atoi(items[2]);
	new->next = NULL;
	new->copy = NULL;
	if (flag == 'S')
		main->graph->start = new;
	else if (flag == 'E')
		main->graph->end = new;
	push_room(main, new);
	cleaner_2_array(items, 3);
}
