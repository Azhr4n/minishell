/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   szero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:02:49 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 17:02:49 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	szero(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}

void	ft_bzero(void *data, int size)
{
	int		i;
	char	*ptr;

	ptr = data;
	i = -1;
	while (++i < size)
		ptr[i] = 0;
}