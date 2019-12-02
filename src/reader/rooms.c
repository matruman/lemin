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
	if (ft_strstr(*line, "##start") && !main->reader->is_start)
	{
		main->reader->is_start = 1;
		ft_memdel((void**)line);
		get_next_line(ch, line);
		main->reader->start = ft_atoi(*line);
		return ;
	}
	else if (ft_strstr(*line, "##end") && !main->reader->is_end)
	{
		main->reader->is_end = 1;
		ft_memdel((void**)line);
		get_next_line(ch, line);
		main->reader->end = ft_atoi(*line);
		return ;
	}
	die();
}

static	void	push_room(t_main *main, t_rd_r *new)
{
	t_rd_r	*tmp;

	main->rooms += 1;
	if (!main->reader->rooms)
	{
		main->reader->rooms = new;
		return ;
	}
	tmp = main->reader->rooms;
	while (tmp->next)
	{
		if ((tmp->x == new->x && tmp->y == new->y)
			|| tmp->number == new->number)
			die();
		tmp = tmp->next;
	}
	if ((tmp->x == new->x && tmp->y == new->y)
		|| tmp->number == new->number)
		die();
	tmp->next = new;
}

int				reader_is_room(t_main *main, char *line)
{
	t_rd_r	*new;
	char	*tmp;
	int		number;

	number = ft_atoi(line);
	if (!(tmp = ft_strchr(line, ' ')))
		return (0);
	if (!(new = (t_rd_r*)malloc(sizeof(t_rd_r))))
		die();
	new->number = number;
	tmp += 1;
	new->x = ft_atoi(tmp);
	if (!(tmp = ft_strchr(tmp, ' ')))
	{
		ft_memdel((void**)&new);
		return (0);
	}
	tmp += 1;
	new->y = ft_atoi(tmp);
	new->next = NULL;
	push_room(main, new);
	return (1);
}
