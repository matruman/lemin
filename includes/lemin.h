/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:23:37 by sjamie            #+#    #+#             */
/*   Updated: 2019/11/12 20:23:38 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include "../gnl/get_next_line.h"
#include <stdio.h>

typedef struct		s_main
{
	int				ants;
	int				rooms;
	int				links;
	struct s_read	*reader;
	struct s_graph	*graph;
}					t_main;

typedef struct		s_read
{
	char			flag;
	int				is_start;
	int				is_end;
	int				start;
	int				end;
	struct s_rd_r	*rooms;
}					t_read;

typedef struct		s_rd_r
{
	int				number;
	int				x;
	int				y;
	struct s_rd_r	*next;
}					t_rd_r;

typedef struct		s_links
{
	int				relation;
	struct s_links	*next;
}					t_links;




typedef struct		s_info
{
	int				count;
	struct s_links	*links;
}					t_info;

typedef struct		s_graph
{
	t_info			**info;
}					t_graph;

void				*lm_init(int res, char *line);
void				die();
void				reader_push(t_main *main, char **line, int ch);

void				reader_words(t_main *main, char **line, int ch);
int					reader_is_room(t_main *main, char *line);
int					reader_is_link(t_main *main, char *line);
void				graph_init(t_main *main);

#endif
