/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 15:27:15 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 15:27:16 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	remove_to_env(t_holder *holder, int index)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (holder->env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size));
	new_env[size - 1] = 0;
	i = 0;
	j = 0;
	while (holder->env[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(holder->env[i]);
			j++;
		}
		free(holder->env[i]);
		i++;
	}
	free(holder->env);
	holder->env = new_env;
}

void	b_unsetenv(t_holder *holder)
{
	int		size;
	int		index;
	int		i;

	size = 0;
	while (holder->data[size])
		size++;
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			index = env_index(holder->env, holder->data[i]);
			if (index != -1)
				remove_to_env(holder, index);
			i++;
		}
	}
}
