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
# define OUTPUT_LEN 80000

# include "stdio.h"
# include "../gnl/get_next_line.h"

typedef struct		s_main
{
	int				ants;
	int				rooms;
	int				links;
	struct s_waybox	*waybox;
	struct s_known	*known;
	struct s_graph	*graph;
	struct s_paths	*paths;
	struct s_paths	*copy_paths;
	struct s_paths	*copy_last;
	struct s_out	*output;
}					t_main;

typedef struct		s_link
{
	char			is_true;
	struct s_node	*old;
	struct s_link	*relink;
	int				llink;
	int				none : 2;
	int				display : 2;
	int				coming : 2;
	int				used;
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
	int				is_known : 2;
	int				is_visit : 2;
	int				split : 8;
	struct s_rel	*linkbox;
	struct s_node	*next;
	struct s_node	*copy;
}					t_node;

typedef struct		s_graph
{
	struct s_paths	*paths;
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

typedef struct		s_waybox
{
	struct s_way	***first;
	struct s_way	***second;
	int				*count_first;
	int				*count_second;
	int				f_score;
	int				s_score;
	int				f_count;
	int				s_count;
	t_node			*start;
	int				passed;
	int				success;
	int				len;
	int				tmp;
	int				*calc;
}					t_waybox;

typedef struct		s_way
{
	char			*name;
	int				ant;
}					t_way;

typedef struct		s_path
{
	int				score;
	t_node			*node;
	struct s_path	*next;
}					t_path;

typedef struct		s_paths
{
	int				s_len;
	int				n_len;
	t_path			*path;
	t_path			*last;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_out
{
	char			*str;
	int				used;
	struct s_out	*next;
}					t_out;

void				*lm_init(int res, char *line);
void				die(void);

void				reader(t_main *main, char **line, int ch);
void				reader_words(t_main *main, char **line, int ch);
void				reader_crtroom(t_main *main, char **items,
									char flag, char *line);
void				reader_crtlink(t_main *main, char **items, char *line);
int					die_atoi(char *str);

int					lm_count(char **items);
void				cleaner_2_array(char **array, int count);

int					dijkstra(t_main *main);
int					get_path(t_main *main, int i);
void				reverse_link(t_node *node, t_link *link);
void				clean_flags(t_main *main);
void				split_path(t_main *main);
t_graph				*merge_paths(t_main *main);

int					search_ways(t_main *main, t_graph *graph);

void				free_way(t_way ***ways, int count, int *ways_counter);
void				free_graph(t_graph *graph, int flag);
void				free_path(t_paths *paths);
void				free_all(t_main *main);

void				run_ants(t_main *main, int flag);
void				swap_link(t_node *sch, t_node *needle,
							t_node *swap, int f);
int					is_set(t_main *main, t_link *link);
int					min_int(int first, int second);
void				cp_paths(t_main *main);
t_node				*copy_node(t_node *node);
void				mark(t_main *main, t_path *path,
							t_paths *paths, t_link *link);
void				set_result(t_way ***ways, int count,
							t_main *main, int *way_counter);
int					ways_count(t_main *main, t_graph *graph);
int					counter(t_way **item);

void				calc_ants(t_main *main, int count, int *way_counter);

t_out				*output_init(void);
void				output_write(t_main *main, char *str, int flag);
void				output_flush(t_main *main, int flag);
void				lm_itoa(t_main *main, int n);

void				sort_way(t_way ***way, int *ways_counter, int count);

void				display_graph(t_graph	*graph);

#endif
