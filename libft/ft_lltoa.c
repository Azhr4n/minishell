/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:23:49 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/18 15:23:51 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static long long int	nb_of_digit(long long int n)
{
	long long int		len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

static void				recur(char **str, long long int len, long long int n)
{
	if ((n / 10) != 0)
	{
		if (n < 0)
			recur(str, len - 1, -(n / 10));
		else
			recur(str, len - 1, n / 10);
	}
	n %= 10;
	if (n < 0)
		n = -n;
	(*str)[len] = '0' + (n % 10);
}

char					*ft_lltoa(long long int n)
{
	char			*ret;
	long long int	len;

	len = nb_of_digit(n);
	if (n < 0)
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len] = 0;
	recur(&ret, len - 1, n);
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
