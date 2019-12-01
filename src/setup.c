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

#include "../includes/lemin.h"

void			reader_push(t_main *main, char **line, int ch)
{
	char	flag;

	flag = 0;
	if (*line[0] == '#')
		reader_words(main, line, ch, &flag);
	if (reader_is_room(main, *line, flag))
		return ;
	if (reader_is_link(main, *line))
		return ;
	die();
}

void			*lm_init(int res, char *line)
{
	t_main	*main;

	if (res < 1 || !(main = (t_main*)malloc(sizeof(t_main))))
		return (NULL);
	if ((main->ants = ft_atoi(line)) < 1)
		return (NULL);
	if (!(main->reader = (t_read*)malloc(sizeof(t_read))))
		return (NULL);
	main->rooms = 0;
	main->links = 0;
	main->reader->rooms = NULL;
	main->reader->links = NULL;
	main->reader->is_start = 0;
	main->reader->is_end = 0;
	return(main);
}
