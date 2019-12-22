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
	ft_putstr("ERROR\n");
	exit(1);
}

static	int		calc(t_main *main)
{
	return (((main->waybox->f_score - 1) *
			(main->waybox->f_count - 1)) < main->ants);
}

static	void	common(t_main *main)
{
	if (!dijkstra(main))
		return (output_flush(main, 1));
	while (dijkstra(main))
	{
		search_ways(main, merge_paths(main));
		if (!calc(main))
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
	if (!(main = (t_main*)lm_init(get_next_line(ch, &line), line)))
		die();
	output_write(main, line, 1);
	ft_memdel((void**)&line);
	while (get_next_line(ch, &line) > 0)
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
