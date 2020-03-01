/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matruman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:32:43 by matruman          #+#    #+#             */
/*   Updated: 2019/09/27 21:00:32 by matruman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 64
# include <unistd.h>
# include "libft/includes/libft.h"
# include <stdlib.h>

int		get_next_line(const int fd, char **line, int f);

#endif
