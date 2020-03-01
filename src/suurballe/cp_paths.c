/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matruman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:40:40 by matruman          #+#    #+#             */
/*   Updated: 2019/12/22 17:40:41 by matruman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_paths	*copy_paths(t_paths *paths, t_main *main)
{
	t_paths *parent;

	if (!(parent = (t_paths*)malloc(sizeof(t_paths))))
		die();
	parent->s_len = paths->s_len;
	parent->n_len = paths->n_len;
	parent->path = NULL;
	parent->next = NULL;
	parent->last = NULL;
	if (!main->copy_paths)
	{
		main->copy_paths = parent;
		main->copy_last = parent;
		return (parent);
	}
	main->copy_last->next = parent;
	main->copy_last = parent;
	return (parent);
}

static	void	copy_path(t_path *path, t_paths *parent)
{
	t_path	*new;

	if (!(new = (t_path*)malloc(sizeof(t_path))))
		die();
	new->node = path->node;
	new->score = path->score;
	new->next = NULL;
	if (!parent->path)
	{
		parent->path = new;
		parent->last = new;
		return ;
	}
	parent->last->next = new;
	parent->last = new;
}

void			cp_paths(t_main *main)
{
	t_paths	*paths;
	t_paths	*c_paths;
	t_path	*path;

	main->copy_paths = NULL;
	paths = main->paths;
	while (paths)
	{
		c_paths = copy_paths(paths, main);
		path = paths->path;
		while (path)
		{
			copy_path(path, c_paths);
			path = path->next;
		}
		paths = paths->next;
	}
}
