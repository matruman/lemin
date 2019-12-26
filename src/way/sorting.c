/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 21:00:06 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/26 21:00:07 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

void			sort_way(t_way ***way, int *ways_counter, int count)
{
	t_way	**tmp1;
	int		tmp;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ways_counter[j] > ways_counter[j + 1])
			{
				tmp1 = way[j];
				way[j] = way[j + 1];
				way[j + 1] = tmp1;
				tmp = ways_counter[j];
				ways_counter[j] = ways_counter[j + 1];
				ways_counter[j + 1] = tmp;
			}
			++j;
		}
		++i;
	}
}
