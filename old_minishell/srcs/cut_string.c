/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 13:25:30 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 13:25:31 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tools.h"

#include <stdio.h>

static int	string_length(char *str, char *cut, int length)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], cut, length))
			return (i);
		i++;
	}
	return (i);
}

char		**cut_string(char *str, char *cut)
{
	char	**ret;
	int		len_cut;
	int		len;

	len_cut = ft_strlen(cut);
	len = string_length(str, cut, len_cut);
	ret = (char **)malloc(sizeof(char *) * 3);
	ret[0] = ft_strndup(str, len);
	ret[1] = ft_strndup(str + len + len_cut, ft_strlen(str) - len - len_cut);
	ret[2] = 0;
	return (ret);
}
