/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:44:48 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/20 12:44:49 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	free_2d(char **array)
{
	char	**base;

	base = array;
	while (*array)
	{
		free(*array);
		array++;
	}
	free(base);
}

void	set_func(t_holder *holder)
{
	holder->b_func[B_ECHO] = b_echo;
	holder->b_func[B_CD] = b_cd;
	holder->b_func[B_ENV] = b_env;
	holder->b_func[B_SETENV] = b_setenv;
	holder->b_func[B_UNSETENV] = b_unsetenv;
}

int		main(int ac, char **av, char **env)
{
	t_holder	holder;
	char		*str;

	(void)ac;
	(void)av;
	cpy_env(&holder, env);
	set_func(&holder);
	while (1)
	{
		if ((str = reading_standard()) != NULL)
		{
			if (*str)
			{
				holder.data = shell_split(str);
				if (holder.data != NULL)
				{
					redirect(&holder);
					free_2d(holder.data);
				}
			}
			free(str);
		}
	}
	free_2d(holder.env);
	return (0);
}
