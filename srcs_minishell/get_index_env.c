/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:26:23 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:26:24 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tools.h"

int		get_index_env(char **env, char *str)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!strcmp_char(env[i], str, '='))
			return (i);
		i++;
	}
	return (-1);
}
