/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:03:06 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/25 15:03:06 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

#include "minishell.h"

static void	exec_command(t_holder *holder)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl("Fork failed.");
		return ;
	}
	if (pid)
		waitpid(pid, &status, 0);
	else if (!pid)
	{
		execve(holder->data[0], holder->data, holder->env);
		ft_putstr("Command not found.\n");
		exit(0);
	}
}

static int	check_tmp(t_holder *holder, char *tmp)
{
	struct stat	buf;

	if (!stat(tmp, &buf))
	{
		free(holder->data[0]);
		holder->data[0] = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

static void	format_command(t_holder *holder)
{
	int		index;
	char	*tmp;
	char	**paths;
	char	**base;

	if (holder->data[0][0] == '/')
		return ;
	if ((index = env_index(holder->env, "PATH")) != -1)
	{
		paths = ft_strsplit((holder->env[index]) + L("PATH="), ':');
		base = paths;
		while (*paths)
		{
			tmp = (char *)malloc(sizeof(char)
				* (L(holder->data[0]) + L(*paths) + 2));
			tmp = ft_strcpy(tmp, *paths);
			tmp = ft_strcat(tmp, "/");
			tmp = ft_strcat(tmp, holder->data[0]);
			if (check_tmp(holder, tmp))
				break ;
			free(tmp);
			paths++;
		}
		free_2d(base);
	}
}

void		process(t_holder *holder)
{
	struct stat	buf;

	format_command(holder);
	if (!stat(holder->data[0], &buf))
		exec_command(holder);
	else
		ft_putstr("Command not found.\n");
}
