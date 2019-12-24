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
#include <ctype.h>

void			die(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

static	int		calc(t_main *main, t_way ***ways, int count)
{
	int		*calc;
	int		final;
	int		tmp;
	int		i;

	if (!(calc = (int*)malloc(sizeof(void*) * count)))
		die();
	i = 0;
	while (i < count)
	{
		calc[i] = counter(ways[i]);
		++i;
	}
	i = 0;
	final = 0;
	tmp = calc[count - 1];
	while (i < count - 1)
	{
		final += tmp - calc[i];
		++i;
	}
	free(calc);
	return (final >= main->ants ? 0 : 1);
}

static	void	common(t_main *main)
{
	if (!dijkstra(main))
		return (output_flush(main, 1));
	while (dijkstra(main))
	{
		search_ways(main, merge_paths(main));
		if (!calc(main, main->waybox->first, main->waybox->f_count))
		{
			fprintf(fopen("testtest", "a"),"%s\n", "FIRST");
			run_ants(main, 1);
			return ;
		}
	}
	fprintf(fopen("testtest", "a"),"%s\n", "LAST");
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
