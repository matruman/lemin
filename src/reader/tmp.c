/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:52:03 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/04 18:52:05 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

int		lm_count(char **items)
{
	int		i;

	i = 0;
	while (items[i])
	{
		i++;
	}
	return (i);
}

void	cleaner_2_array(char **array, int count)
{
	int		i;

	i = 0;
	while (i < count)
		free(array[i++]);
	free(array);
	array = NULL;
}
