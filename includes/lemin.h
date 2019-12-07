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
# define MAXINT 2147483647

#include "../gnl/get_next_line.h"
#include <stdio.h>

typedef struct		s_main
{
	int				ants;
	int				rooms;
	int				links;
	struct s_known	*known;
	struct s_graph	*graph;
	struct s_paths	*paths;
}					t_main;

typedef struct		s_link
{
	char			is_true;
	int				llink;
	struct s_node	*node;
	struct s_link	*next;
}					t_link;

typedef struct		s_rel
{
	int				count;
	struct s_link	*link;
}					t_rel;

typedef struct		s_node
{
	int				id;
	char			*name;
	int				x;
	int				y;
	int				distance;
	int				is_known;
	int				is_visit;
	struct s_rel	*linkbox;
	struct s_node	*next;
}					t_node;

typedef struct		s_graph
{
	struct s_node	*start;
	struct s_node	*end;
	struct s_node	*node;
}					t_graph;

typedef struct		s_known
{
	int				length;
	struct s_node	*node;
	struct s_known	*prev;
	struct s_known	*next;
}					t_known;

typedef struct 		s_path
{
	int				score;
	t_node			*node;
	struct s_path	*next;
}					t_path;

typedef struct 		s_paths
{
	int				s_len;
	int				n_len;
	t_path			*path;
	struct s_paths	*next;
}					t_paths;

void				*lm_init(int res, char *line);
void				die();

void				reader(t_main *main, char **line, int ch);
void				reader_words(t_main *main, char **line, int ch);
void				reader_crtroom(t_main *main, char **items, char flag);
void				reader_crtlink(t_main *main, char **items);

int					lm_count(char **items);
void				cleaner_2_array(char **array, int count);

int					dijkstra(t_main *main);
int					get_path(t_main *main);
void				reverse_link(t_node *node, t_link *link);
void				clean_flags(t_main *main);
void p(void);
#endif
