/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:22:46 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:22:46 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

void	add_to_env(t_data *data, char **opt, int i)
{
	int		index;

	if (is_char(opt[i], '='))
	{
		index = get_index_env(data->env, opt[i]);
		if (index != -1)
		{
			free(data->env[index]);
			data->env[index] = ft_strdup(opt[i]);
		}
		else
			realloc_env(data, opt[i]);
	}
}

void	builtin_setenv(t_data *data, t_btree *btree)
{
	char	**opt;
	int		size;
	int		i;

	opt = split_char(btree->data, ' ');
	size = ft_strlen2d(opt);
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			add_to_env(data, opt, i);
			i++;
		}
	}
	free_2d(opt);
}
