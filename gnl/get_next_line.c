/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjamie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 19:42:42 by sjamie            #+#    #+#             */
/*   Updated: 2019/09/27 19:42:44 by sjamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*gnl_strjoin(char *s1, char const *s2, size_t all)
{
	size_t	j;
	size_t	k;
	char	*string;

	if (!s2)
		return (NULL);
	j = !s1 ? 0 : ft_strlen(s1);
	if (!(string = (char*)malloc((j + all) + 1)))
		return (NULL);
	k = 0;
	if (j)
		while (*s1)
			string[k++] = *s1++;
	while (*s2 && --all)
		string[k++] = *s2++;
	string[k] = '\0';
	return (string);
}

static	size_t	gnl_strsearch(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i++])
		if (str[i - 1] == c)
			return (i);
	return (0);
}

static	size_t	handler(char *str, char **line)
{
	char	*new;
	size_t	i;
	size_t	flag;

	flag = gnl_strsearch(str, '\n');
	new = gnl_strjoin(*line, str, flag ? flag : ft_strlen(str) + 1);
	ft_memdel((void**)line);
	*line = new;
	i = 0;
	while (str[flag] && flag > 0)
		str[i++] = str[flag++];
	while (str[i])
		str[i++] = '\0';
	return (flag);
}

int				get_next_line(const int fd, char **line)
{
	static char	*arr[FD_MAX];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buf, 0) < 0) ||
		(!arr[fd] && !(arr[fd] = ft_strnew(0))))
		return (-1);
	*line = NULL;
	if (arr[fd][0] && handler(arr[fd], line))
		return (1);
	while ((tmp = read(fd, buf, BUFF_SIZE)))
	{
		buf[tmp] = '\0';
		temp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = temp;
		if (handler(arr[fd], line))
			return (1);
	}
	return (*line ? 1 : 0);
}
