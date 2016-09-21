/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:31:38 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 15:31:41 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

void	main_loop(t_data *data)
{
	char	buff[BUFFSIZE + 1];
	int		ret;

	szero(buff, BUFFSIZE + 1);
	ret = 1;
	while (ret != 0)
	{
		write(1, "minishell> ", 10);
		ret = read(0, buff, BUFFSIZE);
		buff[ret - 1] = 0;
		if (ret)
		{
			parsing_precut(data, buff);
			execute_command(data);
			free(data->btree);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	char	**env_cpy;
	t_data	data;
	int		i;

	(void)ac;
	(void)av;
	env_cpy = (char **)malloc(sizeof(char *) * (ft_strlen2d(env) + 1));
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = 0;
	data.env = env_cpy;
	data.btree = 0;
	main_loop(&data);
	free_2d(env_cpy);
	return (0);
}
