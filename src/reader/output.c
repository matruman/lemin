/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:16:17 by sjamie            #+#    #+#             */
/*   Updated: 2019/12/22 20:16:18 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lemin.h"

static	t_out	*get_last(t_main *main)
{
	t_out	*output;

	output = main->output;
	while (output->next)
	{
		output = output->next;
	}
	return (output);
}

t_out			*output_init(void)
{
	t_out	*output;

	if (!(output = (t_out*)malloc(sizeof(t_out))))
		die();
	if (!(output->str = (char*)ft_memalloc((OUTPUT_LEN + 1) * sizeof(char))))
		die();
	output->used = 0;
	output->next = NULL;
	return (output);
}

static	void	output_new_line(t_out *output)
{
	output->str[output->used] = '\n';
	++output->used;
	if (output->used == OUTPUT_LEN - 1)
	{
		output->str[output->used] = 0;
		output->next = output_init();
	}
}

void			output_write(t_main *main, char *str, int flag)
{
	t_out	*output;

	output = get_last(main);
	while (*str)
	{
		output->str[output->used] = *str;
		++output->used;
		++str;
		if (output->used == OUTPUT_LEN - 1)
		{
			output->str[output->used] = 0;
			output->next = output_init();
			return (output_write(main, str, flag));
		}
	}
	if (flag)
		output_new_line(output);
}

void			output_flush(t_main *main, int flag)
{
	t_out	*toutput;
	t_out	*output;

	if (flag)
		output_write(main, "", 1);
	output = main->output;
	while (output)
	{
		toutput = output->next;
		ft_putstr(output->str);
		free(output->str);
		free(output);
		output = toutput;
	}
	main->output = NULL;
}
