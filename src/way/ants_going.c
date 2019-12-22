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

static	int		counter(t_way **item)
{
	int		i;

	i = 0;
	while (item[i])
		++i;
	return (i);
}

static	void	ant_print(char *name, int ant)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static	void	ant_swap(t_main *main, t_way **items, int j, int len)
{
	if (j && items[j - 1]->ant)
	{
		items[j]->ant = items[j - 1]->ant;
		items[j - 1]->ant = 0;
		ant_print(items[j]->name, items[j]->ant);
		if (j == len - 1)
		{
			items[j]->ant = 0;
			main->waybox->success += 1;
		}
		return ;
	}
	if (j || main->ants == main->waybox->passed)
		return ;
	main->waybox->passed += 1;
	items[j]->ant = main->waybox->passed;
	ant_print(items[j]->name, main->waybox->passed);
}

static	void	ants_exec(t_main *main, t_way ***items, int count)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		len = counter(items[i]);
		j = len;
		while (j--)
		{
			if (!items[i][j]->ant)
			{
				ant_swap(main, items[i], j, len);
			}
		}
		++i;
	}
}

void			run_ants(t_main *main, int flag)
{
	t_way	***needle;
	int		count;

	needle = main->waybox->first;
	count = main->waybox->f_count;
	if (flag)
	{
		needle = main->waybox->second;
		count = main->waybox->s_count;
	}
	while (main->waybox->success != main->ants)
	{
		ants_exec(main, needle, count);
		ft_putchar('\n');
	}
}
