/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_ope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:53:15 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 17:53:15 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tools.h"

char	*ft_strdup(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i])
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && i < n)
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*ptr;

	ptr = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
	return (ptr);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = 0;
	return (ptr);
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	char	*ptr;
	int		i;

	ptr = dest;
	i = 0;
	while (*src && i < n - 1)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = 0;
	return (ptr);
}
