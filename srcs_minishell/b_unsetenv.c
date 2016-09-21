/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:21:12 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:21:12 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

void	remove_to_env(t_data *data, int index)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;

	size = ft_strlen2d(data->env);
	new_env = (char **)malloc(sizeof(char *) * (size));
	new_env[size - 1] = 0;
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(data->env[i]);
			j++;
		}
		free(data->env[i]);
		i++;
	}
	free(data->env);
	data->env = new_env;
}

void	builtin_unsetenv(t_data *data, t_btree *btree)
{
	char	**opt;
	int		size;
	int		index;
	int		i;

	opt = split_char(btree->data, ' ');
	size = ft_strlen2d(opt);
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			index = get_index_env(data->env, opt[i]);
			if (index != -1)
				remove_to_env(data, index);
			i++;
		}
	}
	free_2d(opt);
}
