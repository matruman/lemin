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

void			reader(t_main *main, char **line, int ch)
{
	if (*line && *line[0] == '#')
	{
		reader_words(main, line, ch);
		return ;
	}
	if (ft_strchr(*line, ' '))
	{
		reader_crtroom(main, ft_strsplit(*line, ' '), 0, *line);
		return ;
	}
	if (ft_strchr(*line, '-'))
	{
		reader_crtlink(main, ft_strsplit(*line, '-'), *line);
		return ;
	}
	die();
}

void			*free_cost(void *p)
{
	free(p);
	return (0);
}

void			*lm_init(int res, char *line)
{
	t_main	*main;

	if (res < 1 || !(main = (t_main*)malloc(sizeof(t_main))))
		return (NULL);
	if ((main->ants = die_atoi(line)) < 1)
		return (free_cost(main));
	if (!(main->graph = (t_graph*)malloc(sizeof(t_graph))))
		return (NULL);
	if (!(main->waybox = (t_waybox*)malloc(sizeof(t_waybox))))
		return (NULL);
	main->rooms = 0;
	main->links = 0;
	main->graph->node = NULL;
	main->graph->start = NULL;
	main->graph->end = NULL;
	main->paths = NULL;
	main->waybox->passed = 0;
	main->waybox->success = 0;
	main->waybox->first = NULL;
	main->waybox->second = NULL;
	main->copy_paths = NULL;
	main->output = output_init();
	return (main);
}
