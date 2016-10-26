/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 13:04:30 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 13:04:30 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	redirect(t_holder *holder)
{
	static char	*bltin_name[] = {"exit", "echo", "cd", "env", "setenv",
		"unsetenv"};
	int			i;

	if (holder->data[0][0] != '/')
	{
		i = 0;
		while (i < NB_BUILTINS)
		{
			if (!ft_strcmp(holder->data[0], bltin_name[i]))
			{
				if (!i)
					exit(1);
				else
					holder->b_func[i](holder);
				return ;
			}
			i++;
		}
	}
	process(holder);
}
