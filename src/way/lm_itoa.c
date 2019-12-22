/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:29:19 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/07 14:29:20 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	int		ft_itoa_norminette(long n)
{
	long	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void			lm_itoa(t_main *main, int n)
{
	int		i;
	char	string[30];
	long	number;

	number = n;
	i = ft_itoa_norminette(number);
	string[i--] = '\0';
	while (number)
	{
		string[i] = number % 10 + 48;
		i--;
		number /= 10;
	}
	output_write(main, string, 0);
}
