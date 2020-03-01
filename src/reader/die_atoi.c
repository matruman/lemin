/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:43:29 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/22 18:43:31 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

int				die_atoi(char *str)
{
	long long int	num;

	if (ft_strlen(str) > 10)
		die();
	num = 0;
	if (str[0] == '-' || str[1] == '+')
		die();
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	if (*str || num > MAXINT)
		die();
	return (num);
}
