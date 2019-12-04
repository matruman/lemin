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
		reader_crtroom(main, ft_strsplit(*line, ' '), 0);
		return ;
	}
	if (ft_strchr(*line, '-'))
	{
		reader_crtlink(main, ft_strsplit(*line, '-'));
		return ;
	}
	die();
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
