/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:24:10 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:24:11 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

void	realloc_env(t_data *data, char *value)
{
	char	**new_env;
	int		size;
	int		i;

	size = ft_strlen2d(data->env);
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	new_env[size + 1] = 0;
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(value);
	free(data->env);
	data->env = new_env;
}
