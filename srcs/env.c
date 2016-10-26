/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:44:08 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/25 15:44:08 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	cpy_env(t_holder *holder, char **env)
{
	int		count;

	count = 0;
	while (env[count])
		count++;
	holder->env = (char **)malloc(sizeof(char *) * (count + 1));
	holder->env[count] = 0;
	count = 0;
	while (env[count])
	{
		holder->env[count] = ft_strdup(env[count]);
		count++;
	}
}

int		env_index(char **env, char *name)
{
	int		index;

	index = 0;
	while (*env && ft_strncmp(*env, name, ft_strlen(name)) != 0)
	{
		index++;
		env++;
	}
	if (!*env)
		return (-1);
	return (index);
}

void	realloc_env(t_holder *holder, char *value)
{
	char	**new_env;
	int		size;
	int		i;

	size = 0;
	while (holder->env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	new_env[size + 1] = 0;
	i = 0;
	while (holder->env[i])
	{
		new_env[i] = ft_strdup(holder->env[i]);
		free(holder->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(value);
	free(holder->env);
	holder->env = new_env;
}

void	b_env(t_holder *holder)
{
	char	**env;

	env = holder->env;
	while (*env)
	{
		ft_putendl(*env);
		env++;
	}
}
