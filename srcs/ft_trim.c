/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 12:21:30 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 12:21:31 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tools.h"

#include <stdio.h>

static int	calc_length(char *str)
{
	int		i;
	int		length;
	int		flag;

	i = 0;
	length = 0;
	while (str[i])
	{
		if (!flag && (str[i] == ' ' || str[i] == '\t'))
		{
			flag = 1;
			length = i;
		}
		else if (str[i] != ' ' && str[i] != '\t')
			flag = 0;
		i++;
	}
	if (!flag)
		length = i;
	return (length);
}

char		*trim(char *str)
{
	char	*ret;
	int		length;

	while (*str == ' ' || *str == '\t')
		str++;
	length = calc_length(str);
	ret = (char *)malloc(sizeof(char) * (length + 1));
	ret = ft_strncpy(ret, str, length + 1);
	return (ret);
}
