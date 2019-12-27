/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_going.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:52:37 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/17 20:52:38 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	void	ant_print(t_main *main, char *name, int ant)
{
	output_write(main, "L", 0);
	lm_itoa(main, ant);
	output_write(main, "-", 0);
	output_write(main, name, 0);
	output_write(main, " ", 0);
}

static	void	ant_swap(t_main *main, t_way **items, int j, int i)
{
	if (j && items[j - 1]->ant)
	{
		items[j]->ant = items[j - 1]->ant;
		items[j - 1]->ant = 0;
		ant_print(main, items[j]->name, items[j]->ant);
		if (j == main->waybox->len - 1)
		{
			items[j]->ant = 0;
			main->waybox->success += 1;
		}
		return ;
	}
	if (j || main->ants == main->waybox->passed || !main->waybox->calc[i])
		return ;
	main->waybox->calc[i] -= 1;
	main->waybox->passed += 1;
	items[j]->ant = main->waybox->passed;
	ant_print(main, items[j]->name, main->waybox->passed);
}
#include "ctype.h"
static	void	ants_exec(t_main *main, t_way ***items,
							int count, int *way_counter)
{
	int		len;
	int		i;
	int		j;
FILE *fd ;
fd= fopen("fdfdfd", "a");
	i = 0;
	while (i < count)
	{
		len = way_counter[i];
		main->waybox->len = len;
		j = 0;
		fprintf(fd ,"#%d  len: %d ants: %d = ", i, len, main->waybox->calc[i]);
	//	j = len;
		while (j < len)
		{
			fprintf(fd ," %s", items[i][j]->name);
			++j;
			// if (!items[i][j]->ant)
			// {
			// 	ant_swap(main, items[i], j, i);
			// }
		}
		fprintf(fd ,"\n\n");
		++i;
	}
}

void			run_ants(t_main *main, int flag)
{
	t_way	***needle;
	int		*way_counter;
	int		count;

	needle = main->waybox->first;
	way_counter = main->waybox->count_first;
	count = main->waybox->f_count;
	if (flag)
	{
		needle = main->waybox->second;
		way_counter = main->waybox->count_second;
		count = main->waybox->s_count;
	}

	calc_ants(main, needle, count, way_counter);
//	output_flush(main, 1);
	main->output = output_init();
// 	while (main->waybox->success != main->ants)
// 	{
 		ants_exec(main, needle, count, way_counter);
// //		output_write(main, "", 1);
// 	}
//	output_flush(main, 0);
}
