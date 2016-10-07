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

#include <stdio.h>

char	*magic(t_echo *echo)
{
	char	*str;
	t_echo	*ptr;
	int		length;
	int		pos;

	ptr = echo;
	length = 0;
	while (ptr)
	{
		length += ft_strlen(ptr->buff);
		ptr = ptr->next;
	}
	str = (char *)malloc(sizeof(char) * (length + 1));
	ft_bzero(str, length * (sizeof(char)) + 1);
	ptr = echo;
	pos = 0;
	while (ptr)
	{
		ft_strcpy(&str[pos], ptr->buff);
		pos += ft_strlen(ptr->buff);
		ptr = ptr->next;
	}
	return (str);
}

void	main_loop(t_data *data)
{
	char	buff[BUFFSIZE + 1];
	char	*str;
	t_echo	*echo;
	int		ret;

	echo = NULL;
	szero(buff, BUFFSIZE + 1);
	ret = 0;
	while (1)
	{
		if (ret < BUFFSIZE)
			write(1, "minishell> ", 10);
		if ((ret = read(0, buff, BUFFSIZE)) < 0)
			exit(1);
		buff[ret] = 0;
		if (buff[ret - 1] == '\n')
		{
			buff[ret - 1] = 0;
			ret = 0;
		}
		if (ret >= 0 && ret < BUFFSIZE)
		{
			if (echo != NULL)
				str = magic(echo);
			else
				str = ft_strdup(buff);
			parsing_precut(data, str);
			execute_command(data);
			free(data->btree);
			free(str);
			clean_list(echo);
			echo = NULL;
		}
		else if (ret == BUFFSIZE)
			add_echo_at_end(&echo, buff);
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
