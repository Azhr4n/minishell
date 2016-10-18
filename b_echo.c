/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:28:05 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/18 15:28:05 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

#include <stdio.h>

int			valid_options(char *ptr, char *array)
{
	char	*ret;

	while (*ptr && *ptr != ' ' && *ptr != '\t')
	{
		if ((ret = ft_strchr(array, *ptr)) == NULL)
			return (0);
		ptr++;
	}
	return (1);
}

void		seek_options(char **data, void *options_addr, char *array)
{
	int			*options;
	char		*ptr;
	char		*ret;

	options = options_addr;
	while (**data && (**data == '\t' || **data == ' '))
		(*data)++;
	ptr = *data;
	if (*ptr == '-')
	{
		ptr++;
		if (valid_options(ptr, array))
		{
			while (*ptr && *ptr != ' ' && *ptr != '\t')
			{
				if ((ret = ft_strchr(array, *ptr)) != NULL)
					options[ret - array] = 1;
				ptr++;
			}
			*data = ptr;
			seek_options(data, options_addr, array);
		}
	}
}

void		echo(char *data)
{
	int		options[NB_ECHO];

	ft_bzero(&options, NB_ECHO * sizeof(int));
	seek_options(&data, &options, "ne");

	for (int i = 0; i < NB_ECHO; i++) {
		printf("options : %d\n", options[i]);
	}

}

int			main(void)
{
	echo(" 	 	 	 -nnnee 	 -ve 	 -e 	 	'Bonjour ceci est un test'");
	return (0);
}