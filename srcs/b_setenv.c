/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 15:20:42 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 15:20:42 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	add_to_env(t_holder *holder, int i)
{
	int		index;

	if ((ft_strchr(holder->data[i], '=')) != NULL)
	{
		index = env_index(holder->env, holder->data[i]);
		if (index != -1)
		{
			free(holder->env[index]);
			holder->env[index] = ft_strdup(holder->data[i]);
		}
		else
			realloc_env(holder, holder->data[i]);
	}
}

void	b_setenv(t_holder *holder)
{
	int		size;
	int		i;

	size = 0;
	while (holder->data[size])
		size++;
	if (size > 1)
	{
		i = 1;
		while (i < size)
		{
			add_to_env(holder, i);
			i++;
		}
	}
}
