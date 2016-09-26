/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:18:19 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:18:19 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"
#include "tools.h"

void	exec_command(t_data *data, t_btree *btree, char buffer[BUFFSIZE + 1])
{
	pid_t	pid;
	int		status;
	char	**opt;

	opt = split_space(btree->data);
	pid = fork();
	if (pid == -1)
	{
		free_2d(opt);
		ft_putendl("Fork failed.");
		return ;
	}
	if (pid)
	{
		waitpid(pid, &status, 0);
		free_2d(opt);
	}
	else if (!pid)
	{
		execve(buffer, opt, data->env);
		exit(0);
	}
}

int		split_paths(t_data *data, char ***paths)
{
	int		env_index;

	env_index = get_index_env(data->env, "PATH");
	if (env_index == -1)
		return (0);
	*paths = split_char(data->env[env_index] + 5, ':');
	return (1);
}

void	search_then_exec(t_data *data, t_btree *btree)
{
	char			buffer[BUFFSIZE + 1];
	struct stat		buf;
	char			**path;
	int				i;

	if (split_paths(data, &path))
	{
		i = -1;
		while (path[++i])
		{
			szero(buffer, BUFFSIZE + 1);
			if (btree->data[0] != '/')
			{
				ft_strcpy(buffer, path[i]);
				ft_strcat(buffer, "/");
			}
			strcat_char(buffer, btree->data, ' ');
			if (!stat(buffer, &buf))
			{
				exec_command(data, btree, buffer);
				free_2d(path);
				return ;
			}
		}
	}
	write(2, "Command not found.\n", 20);
}

void	exec_separator(t_data *data, t_btree *btree)
{
	if (!ft_strcmp(btree->data, "&&"))
	{
		if (!call_builtin(data, btree->left))
			search_then_exec(data, btree->left);
	}
}

void	execute_command(t_data *data)
{
	t_btree	*btree;
	int		i;

	i = 0;
	while (data->btree[i])
	{
		btree = data->btree[i];
		while (btree->right)
		{
			if (btree->type == SEPARATOR)
				exec_separator(data, btree);
			btree = btree->right;
		}
		if (!call_builtin(data, btree))
			search_then_exec(data, btree);
		free_btree(data->btree[i]);
		i++;
	}
}
