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

#include "../includes/lemin.h"

void			reader_words(t_main *main, char **line, int ch, char *flag)
{
	if (ft_strstr(*line, "##start") && !main->reader->is_start)
	{
		*flag = 's';
		main->reader->is_start = 1;
		ft_memdel((void**)line);
		get_next_line(ch, line);
		return ;
	}
	else if (ft_strstr(*line, "##end") && !main->reader->is_end)
	{
		*flag = 'e';
		main->reader->is_end = 1;
		ft_memdel((void**)line);
		get_next_line(ch, line);
		return ;
	}
	die();
}

static	void	push_room(t_main *main, t_rd_r *new)
{
	main->rooms += 1;
	if (!main->reader->rooms)
	{
		main->reader->rooms = new;
		main->reader->r_next = main->reader->rooms;
		return ;
	}
	main->reader->r_next->next = new;
	main->reader->r_next = new;
}

int				reader_is_room(t_main *main, char *line, char flag)
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
	new->flag = flag;
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

static	void	push_link(t_main *main, t_rd_l *new)
{
	main->links += 1;
	if (!main->reader->links)
	{
		main->reader->links = new;
		main->reader->l_next = main->reader->links;
		return ;
	}
	main->reader->l_next->next = new;
	main->reader->l_next = new;
}

int				reader_is_link(t_main *main, char *line)
{
	t_rd_l	*new;
	char	*tmp;

	if (!(new = (t_rd_l*)malloc(sizeof(t_rd_l))))
		die();
	new->first = ft_atoi(line);
	if (!(tmp = ft_strchr(line, '-')))
		return (0);
	tmp += 1;
	new->second = ft_atoi(tmp);
	new->next = NULL;
	push_link(main, new);
	return (1);
}
