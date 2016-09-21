/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:23:39 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:23:39 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"
#include "tools.h"

static void	print_env(char **env)
{
	while (*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}

void		builtin_env(t_data *data, t_btree *btree)
{
	char	**opt;
	int		size;

	opt = split_char(btree->data, ' ');
	size = ft_strlen2d(opt);
	if (size == 1)
		print_env(data->env);
	free_2d(opt);
}
