/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 17:35:16 by pivanovi          #+#    #+#             */
/*   Updated: 2016/02/24 16:19:24 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "get_next_line.h"
#include "libft.h"

char		*strjoinf(char *s1, const char *s2, int len)
{
	char	*ret;
	int		index;
	int		i;
	int		j;

	if ((ret = (char *)malloc(sizeof(char)
		* (ft_strlen(s1) + len + 1))) == NULL)
		return (NULL);
	index = 0;
	j = 0;
	while (s1[j])
	{
		ret[index] = s1[j];
		index++;
		j++;
	}
	i = 0;
	while (i < len)
	{
		ret[index + i] = s2[i];
		i++;
	}
	ret[index + i] = 0;
	free(s1);
	return (ret);
}

int			gnl(char **line, char buffer[BUFF_SIZE])
{
	char	*ptr;

	if ((ptr = ft_strchr(buffer, '\n')) != NULL)
	{
		*line = strjoinf(*line, buffer, (int)(ptr - buffer));
		ft_strcpy(buffer, ptr + 1);
		return (1);
	}
	else
	{
		*line = strjoinf(*line, buffer, ft_strlen(buffer));
		buffer[0] = 0;
		return (0);
	}
}

int			get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE + 1];
	int			ret;
	int			stop;

	if ((void *)line == 0)
		return (-1);
	if ((*line = (char *)malloc(sizeof(char))) == NULL)
		return (-1);
	(*line)[0] = 0;
	stop = 0;
	ret = 1;
	while (!stop && ret > 0)
	{
		if (!buffer[0])
		{
			if ((ret = read(fd, buffer, BUFF_SIZE)) == -1)
				return (ret);
			buffer[ret] = 0;
			if (ret < BUFF_SIZE)
				stop = 1;
		}
		stop = gnl(line, buffer);
	}
	return ((!ret && !(*line[0])) ? 0 : 1);
}
