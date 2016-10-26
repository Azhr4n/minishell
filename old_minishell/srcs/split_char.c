/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:35:05 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 15:35:06 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tools.h"

static int	words_number(char *str, char c)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (!flag && *str != c)
		{
			flag = 1;
			i++;
		}
		str++;
		if (*str == c)
			flag = 0;
	}
	return (i);
}

static int	word_length(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char		**split_char(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	while (*str == c)
		str++;
	tab = (char **)malloc(sizeof(char *) * (words_number(str, c) + 1));
	i = 0;
	while (*str)
	{
		tab[i] = (char *)malloc(sizeof(char) * (word_length(str, c) + 1));
		j = 0;
		while (*str && *str != c)
		{
			tab[i][j] = *str;
			str++;
			j++;
		}
		tab[i][j] = 0;
		while (*str && (*str == c))
			str++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
