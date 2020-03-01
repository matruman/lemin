/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:25:03 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/24 18:25:04 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	int		calc_formula(int *calc, int res, int tmp, int count)
{
	int		final;
	int		i;

	final = 0;
	i = count - 1;
	while (i--)
		res -= tmp - calc[i];
	res /= count;
	i = count - 1;
	calc[i] = res;
	final += calc[i];
	while (i--)
	{
		calc[i] = res + (tmp - calc[i]);
		final += calc[i];
	}
	return (final);
}

static	void	calc_add(int *calc, int difference, int count)
{
	int		i;

	i = 0;
	while (i < difference && i < count)
	{
		calc[i] += 1;
		++i;
	}
	if (difference > i)
		return (calc_add(calc, difference - i, count));
}

static	void	calc_remove(int *calc, int difference, int count)
{
	int		i;

	i = count;
	while (difference && i--)
	{
		calc[i] -= 1;
		--difference;
	}
	if (difference)
		return (calc_remove(calc, difference, count));
}

void			calc_ants(t_main *main, int count, int *way_counter)
{
	int		*calc;
	int		i;

	if (!(calc = (int*)malloc(sizeof(int) * count)))
		die();
	i = 0;
	while (i < count)
	{
		calc[i] = way_counter[i];
		++i;
	}
	i = calc_formula(calc, main->ants, calc[count - 1], count);
	if (i < main->ants)
		calc_add(calc, main->ants - i, count);
	if (main->ants < i)
		calc_remove(calc, i - main->ants, count);
	main->waybox->calc = calc;
}
