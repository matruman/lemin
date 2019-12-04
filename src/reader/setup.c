/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:01:44 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/01 17:01:45 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

// void			graph_init(t_main *main)
// {
// 	t_graph	*graph;
// 	t_info	**info;
// 	size_t	i;

// 	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
// 		die();
// 	if (!(graph->info = (t_info**)malloc(sizeof(t_info*) *
// 		(main->rooms + 1))))
// 		die();
// 	i = 0;
// 	while (i < main->rooms)
// 	{
// 		if (!(graph->info[i] = (t_info*)malloc(sizeof(t_info))))
// 			die();
// 		graph->info[i]->count = 0;
// 		graph->info[i]->links = NULL;
// 		i++;
// 	}
// 	graph->info[i] = NULL;
// 	main->graph = graph;
// 	main->reader->flag = 'Y';
// }

void			reader(t_main *main, char **line, int ch)
{
	if (*line && *line[0] == '#')
	{
		reader_words(main, line, ch);
		return ;
	}
	if (ft_strchr(*line, ' '))
	{
		reader_crtroom(main, ft_strsplit(*line, ' '), 0);
		return ;
	}
	// if (ft_strchr(*line, '-'))
	// 	printf("%s\n", "b");
	// if (reader_is_room(main, *line))
	// 	return ;
	// if (reader_is_link(main, *line))
	// 	return ;
	// die();
}

void			*lm_init(int res, char *line)
{
	t_main	*main;

	if (res < 1 || !(main = (t_main*)malloc(sizeof(t_main))))
		return (NULL);
	if ((main->ants = ft_atoi(line)) < 1)
		return (NULL);
	if (!(main->graph = (t_graph*)malloc(sizeof(t_graph))))
		return (NULL);
	main->rooms = 0;
	main->links = 0;
	main->graph->node = NULL;
	main->graph->start = NULL;
	main->graph->end = NULL;
	return(main);
}
