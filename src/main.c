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
	// while (dijkstra(main));

	dijkstra(main);
	dijkstra(main);
		// t_node *a1;
		// t_link *a2;

		// a1 = main->graph->node;
		// while (a1)
		// {
		// 	printf("%s%c: ", a1->name, a1->split);
		// 	a2 = a1->linkbox->link;
		// 	while (a2)
		// 	{
		// 		printf(">%s%c %d< ", a2->node->name, a2->node->split, a2->is_true);
		// 		a2 = a2->next;
		// 	}
		// 	printf("\n\n");
		// 	a1 = a1->next;
		// }
	display_graph(main->graph);
	return (0);
}
