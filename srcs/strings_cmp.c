/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:13:36 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 13:41:49 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

#include <stdio.h>

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int		ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (*s1 && *s2 && *s1 == *s2 && i < n - 1)
	{
		s1++;
		s2++;
		i++;
	}
	return (*s1 - *s2);
}

int		is_char(char *s1, char c)
{
	while (*s1)
	{
		if (*s1 == c)
			return (1);
		s1++;
	}
	return (0);
}
