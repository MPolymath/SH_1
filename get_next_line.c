/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 21:55:05 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/01 14:26:41 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

int				ft_freejoin(char **line, char *str)
{
	char		*tmp;

	if (*str)
	{
		tmp = *line;
		if (*line == NULL)
			*line = ft_strdup(str);
		else
			*line = ft_strjoin(*line, str);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (*line == NULL)
			return (-1);
		ft_bzero(str, BUFF_SIZE);
	}
	return (0);
}

int				ft_trunc(char *buff, char **line)
{
	char		tmp[BUFF_SIZE];
	int			i;
	int			j;

	ft_bzero(tmp, BUFF_SIZE);
	i = -1;
	while (buff[++i] && buff[i] != '\n')
		tmp[i] = buff[i];
	if (ft_freejoin(line, tmp) == -1)
		return (-1);
	j = -1;
	while (buff[++i])
		tmp[++j] = buff[i];
	ft_bzero(buff, BUFF_SIZE);
	ft_strcpy(buff, tmp);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static char	buff[BUFF_SIZE];
	int			rd;

	*line = NULL;
	rd = 0;
	while (*buff || (rd = read(fd, buff, BUFF_SIZE)))
	{
		if (rd < 0)
			return (-1);
		if (ft_strchr(buff, '\n'))
			return (ft_trunc(buff, line));
		if (ft_freejoin(line, buff) == -1)
			return (-1);
	}
	return (0);
}
