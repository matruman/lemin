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
}					t_main;

typedef struct		s_read
{
	int				is_start;
	int				is_end;
	struct s_rd_r	*rooms;
	struct s_rd_r	*r_next;
	struct s_rd_l	*links;
	struct s_rd_l	*l_next;
}					t_read;

typedef struct		s_rd_r
{
	char			flag;
	int				number;
	int				x;
	int				y;
	struct s_rd_r	*next;
}					t_rd_r;

typedef struct		s_rd_l
{
	int				first;
	int				second;
	struct s_rd_l	*next;
}					t_rd_l;

void				*lm_init(int res, char *line);
void				die();
void				reader_push(t_main *main, char **line, int ch);

void				reader_words(t_main *main, char **line, int ch, char *flag);
int					reader_is_room(t_main *main, char *line, char flag);
int					reader_is_link(t_main *main, char *line);

#endif
