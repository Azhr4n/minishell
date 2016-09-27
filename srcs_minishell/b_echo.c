/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:37:32 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/27 12:37:32 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

int		get_index(char c)
{
	static char	tab[NB_BS_OPT] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\'};
	int			i;

	i = -1;
	while (++i < NB_BS_OPT)
	{
		if (tab[i] == c)
			return (i);
	}
	return (-1);
}

void	echo(char *data, int *options)
{
	static char	tab[NB_BS_OPT] = {'\a', '\b', '\f', '\n',
		'\r', '\t', '\v', '\\'};
	int			index;
	int			g;

	t_echo		*echo;

	echo = NULL;
	add_echo_at_end("bonjour ceci est un test");

	g = 0;
	while (*data)
	{
		if (*data == '\'' || *data == '\"')
			g = SWAP(g);
		if (*data != '\'' && *data != '\"')
		{
			if (*data == '\\' && g && options[ECHO_E])
			{
				if ((index = get_index(*(data + 1))) != -1)
					write(1, &tab[index], 1);
				else
					write(1, data, 1);
				data++;
			}
			else
				write(1, data, 1);
		}
		data++;
	}
}

char	*which_opt(char *data, int *options)
{
	char	*ptr;

	while (*data)
	{
		ptr = data;
		while (*data == '-' || *data == 'e' || *data == 'n')
		{
			if (*data == 'e')
				options[ECHO_E] = 1;
			else if (*data == 'n')
				options[ECHO_N] = 1;
			data++;
			if (*data == '-')
				return (ptr);
		}
		if (*data == ' ' || *data == '\t')
		{
			data++;
			ptr = data;
		}
		else
			return (ptr);
	}
	return (data);
}

int		builtin_echo(t_btree *btree)
{
	char	**opt;
	char	*ptr;
	int		size;
	int		*options;

	if ((options = (int *)malloc(sizeof(int) * NB_ECHO_OPT)) == NULL)
		return (1);
	ft_bzero(options, NB_ECHO_OPT * sizeof(int));
	size = 0;
	opt = split_char(btree->data, ' ');
	while (opt[size])
		size++;
	if (size == 1)
		write(1, "\n", 1);
	else
	{
		ptr = which_opt(btree->data + 5, options);
		echo(ptr, options);
		if (!options[ECHO_N])
			write(1, "\n", 1);
	}
	free(options);
	free_2d(opt);
	return (1);
}
