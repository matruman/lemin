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

void	display_graph(t_graph	*graph);

void			die()
{
	ft_putstr("ERROR\n");
	exit(1);	
}
void p(void) {printf("HELLO\n");}
int				main(void)
{
	t_main	*main;
	char	*line;
	int		ch;

	line = NULL;
	if ((ch = open("map2.txt", O_RDONLY)) == -1)
		die();
	if (!(main = (t_main*)lm_init(get_next_line(ch, &line), line)))
		die();
	ft_memdel((void**)&line);
	while (get_next_line(ch, &line) > 0)
	{
		if (!(line[0] == '#' && line[1] != '#'))
			reader(main, &line, ch);
		ft_memdel((void**)&line);
	}
	while (dijkstra(main));
	display_graph(main->graph);
	return (0);
}
