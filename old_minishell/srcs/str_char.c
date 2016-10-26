/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 16:18:28 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 16:18:28 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*strcpy_char(char *dest, char *src, char c)
{
	char	*ptr;

	ptr = dest;
	while (*src && *src != c)
	{
		*dest = *src;
		src++;
		dest++;
	}
	return (ptr);
}

char	*strcat_char(char *dest, char *src, char c)
{
	char	*ptr;

	ptr = dest;
	while (*dest)
		dest++;
	while (*src && *src != c)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
	return (ptr);
}

int		strcmp_char(char *s1, char *s2, char c)
{
	while (*s1 && *s2 && *s1 == *s2 && *s1 != c)
	{
		s1++;
		s2++;
	}
	if (!*s2 && *s1 == c)
		return (0 - *s2);
	return (*s1 - *s2);
}

int		strlen_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
