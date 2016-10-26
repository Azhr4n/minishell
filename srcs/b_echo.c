/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 16:25:09 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/21 16:25:09 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

#include <stdio.h>

static int	get_opt(char **array)
{
	char	*str;
	int		count;

	count = 0;
	if (*array)
	{
		str = *array;
		if (*str == '-')
		{
			str++;
			while (*str == 'n')
				str++;
			if (!(*str))
			{
				count++;
				count += get_opt(array + 1);
			}
		}
	}
	return (count);
}

static int	print_env_key(char **env, char *str, int *printed)
{
	int		count;
	int		index;
	char	*env_key;

	count = 0;
	while (str[count] && str[count] != ' ' && str[count] != '\t')
		count++;
	env_key = (char *)malloc(sizeof(char) * (count + 1));
	env_key = ft_strncpy(env_key, str, count);
	index = env_index(env, env_key);
	if (index != -1)
	{
		ft_putstr(env[index] + count + 1);
		*printed = 1;
	}
	free(env_key);
	return (count);

}

static int	e_print(char **env, char *str)
{
	int		printed;

	printed = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			str += print_env_key(env, str, &printed);
		}
		else
		{
			ft_putchar(*str);
			printed = 1;
		}
		str++;
	}
	return (printed);
}

void		b_echo(t_holder *holder)
{
	char	**data;
	int		skip;
	int		printed;

	skip = get_opt(&holder->data[1]);
	data = &holder->data[1 + skip];
	printed = 0;
	while (*data)
	{
		if (printed)
			ft_putchar(' ');
		printed = e_print(holder->env, *data);
		data++;
	}
	if (!skip)
		ft_putchar('\n');
}
