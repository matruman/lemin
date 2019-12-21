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
void p(void) {printf("HELLO\n");}
void			die()
{
	ft_putstr("ERROR\n");
	exit(1);	
}

static	int		calc(t_main *main)
{
	return (((main->waybox->f_score - 1) *
			(main->waybox->f_count - 1)) < main->ants);
}

// static	void	common(t_main *main)
// {
// 	t_graph	*result;

// 	if (!dijkstra(main))
// 		return ;
// 	if (!calc(main))
// 		return (run_ants(main, 0));
// 	while (dijkstra(main))
// 	{
// 		result = merge_paths(main);
// 		search_ways(main, result);
// 		if (!calc(main))
// 			return (run_ants(main, 0));
// 	}
// 	run_ants(main, 1);
// }

static	void	common(t_main *main)
{
	t_graph	*result;

	if (!dijkstra(main))
		return ;
	while (dijkstra(main))
	{
		result = merge_paths(main);
	//	p();
		// t_node *a1;
		// t_link *a2;

		// a1 = result->node;
		// while (a1)
		// {
		// 	printf("%s%c: ", a1->name, a1->split);
		// 	a2 = a1->linkbox->link;
		// 	while (a2)
		// 	{
		// 		printf(">%s %d< ", a2->node->name, a2->is_true);
		// 		a2 = a2->next;
		// 	}
		// 	printf("\n\n");
		// 	a1 = a1->next;
		// }
		// display_graph(result);
		// return ;
		// display_graph(result);
		// return ;
		search_ways(main, result);
		if (!calc(main))
		{
			ft_putstr("323232\n");
			run_ants(main, 1);
	//		display_graph(result);
			return ;
		}
	}
	ft_putstr("sdsd\n");
	run_ants(main, 0);
		// t_node *a1;
		// t_link *a2;

		// a1 = main->graph->node;
		// while (a1)
		// {
		// 	printf("%s%c: ", a1->name, a1->split);
		// 	a2 = a1->linkbox->link;
		// 	while (a2)
		// 	{
		// 		printf(">%s%c %d< ", a2->node->name, a1->split, a2->is_true);
		// 		a2 = a2->next;
		// 	}
		// 	printf("\n");
		// 	a1 = a1->next;
		// }
 //	display_graph(main->graph);
}


int				main(int a, char **b)
{
	t_main	*main;
	char	*line;
	int		ch;

	line = NULL;
	if ((ch = open(b[1], O_RDONLY)) == -1)
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
	// 	t_node *a1;
	// 	t_link *a2;

	// 	a1 = main->graph->node;
	// 	while (a1)
	// 	{
	// 		printf("%s%c: ", a1->name, a1->split);
	// 		a2 = a1->linkbox->link;
	// 		while (a2)
	// 		{
	// 			printf(">%s %s< ", a2->node->name, a2->relink->node->name);
	// 			a2 = a2->next;
	// 		}
	// 		printf("\n\n");
	// 		a1 = a1->next;
	// 	}
	// exit(0);
	common(main);
	return (0);
}
