/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 22:19:24 by sjamie            #+#    #+#             */
/*   Updated: 2019/11/10 22:19:26 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			die(void)
{
	get_next_line(0, 0, 1);
	ft_putstr("ERROR\n");
	exit(1);
}

static	int		calc(t_main *main, int count, int *way_counter)
{
	int		final;
	int		tmp;
	int		i;

	i = 0;
	final = 0;
	tmp = way_counter[count - 1];
	while (i < count - 1)
	{
		final += tmp - way_counter[i];
		++i;
	}
	return (final + 1 > main->ants || count > main->ants ? 1 : 0);
}

static	void	common(t_main *main)
{
	if (!dijkstra(main))
		die();
	while (dijkstra(main))
	{
		search_ways(main, merge_paths(main));
		if (calc(main, main->waybox->f_count, main->waybox->count_first))
		{
			run_ants(main, 1);
			return ;
		}
	}
	run_ants(main, 0);
}

int				main(void)
{
	t_main	*main;
	char	*line;
	int		ch;

	line = NULL;
	ch = 0;
	if (!(main = (t_main*)lm_init(get_next_line(ch, &line, 0), line)))
		die();
	output_write(main, line, 1);
	ft_memdel((void**)&line);
	while (get_next_line(ch, &line, 0) > 0)
	{
		if (!(line[0] == '#' && line[1] != '#'))
			reader(main, &line, ch);
		output_write(main, line, 1);
		ft_memdel((void**)&line);
	}
	if (!main->graph->start || !main->graph->end)
		die();
	common(main);
	return (0);
}
