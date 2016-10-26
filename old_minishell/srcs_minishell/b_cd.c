/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:24:44 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:24:45 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

static void	cd_opt_dir(t_data *data, char **opt)
{
	DIR		*fd;

	if (strcmp_char(opt[1], "-", ' ') && ft_strncmp(opt[1], "~", 1))
	{
		fd = opendir(opt[1]);
		if (fd)
		{
			change_dir(data, opt[1]);
			closedir(fd);
		}
		else
			write(1, "You don't have the rights to do that.\n", 38);
	}
}

void		cd_opt_tild(t_data *data, char **opt)
{
	DIR		*fd;
	char	*path;
	int		index;

	if (!ft_strncmp(opt[1], "~", 1))
	{
		if ((index = get_index_env(data->env, "HOME")) != -1)
		{
			if ((path = (char *)malloc(sizeof(char) * (ft_strlen(data->env[index]
				+ ft_strlen("HOME=")) + ft_strlen(opt[1])))) == NULL)
				return ;
			path = ft_strcpy(path, data->env[index] + ft_strlen("HOME="));
			path = ft_strcat(path, opt[1] + 1);
			if ((fd = opendir(path)))
			{
				change_dir(data, path);
				closedir(fd);
			}
			else
				write(1, "Path inexistant.\n", 17);
			free(path);
		}
		else
			write(1, "No HOME in environment.\n", 24);
	}
}

static void	cd_opt_minus(t_data *data, char **opt)
{
	DIR		*fd;
	char	*path;
	int		index;

	if (!strcmp_char(opt[1], "-", ' '))
	{
		index = get_index_env(data->env, "OLDPWD");
		if (index != -1)
		{
			path = data->env[index] + ft_strlen("OLDPWD=");
			fd = opendir(path);
			if (fd)
			{
				change_dir(data, path);
				closedir(fd);
			}
			else
				write(1, "You don't have the rights to do that.\n", 38);
		}
		else
			write(1, "No oldpwd in environment.\n", 26);
	}
}

static void	cd_no_opt2(t_data *data, DIR *fd, char *path)
{
	char	buff[BUFFSIZE + 1];
	char	*ret;

	if (fd)
	{
		szero(buff, BUFFSIZE + 1);
		ret = getcwd(buff, BUFFSIZE);
		if ((chdir(path)) == -1)
		{
			write(2, "Chdir failed.\n", 14);
			return ;
		}
		if (ret)
			set_oldpwd(data, buff);
		set_pwd(data);
		closedir(fd);
	}
	else
		write(1, "You don't have the rights to do that.\n", 38);
}

static void	cd_no_opt(t_data *data)
{
	DIR		*fd;
	int		index;
	char	*path;

	index = get_index_env(data->env, "HOME");
	if (index != -1)
	{
		path = data->env[index] + ft_strlen("HOME=");
		fd = opendir(path);
		cd_no_opt2(data, fd, path);
	}
	else
		write(1, "No HOME in env.\n", 16);
}

void		builtin_cd(t_data *data, t_btree *btree)
{
	char	**opt;
	int		size;

	opt = split_char(btree->data, ' ');
	size = 0;
	while (opt[size])
		size++;
	if (size == 1)
		cd_no_opt(data);
	else if (size == 2)
	{
		cd_opt_minus(data, opt);
		cd_opt_tild(data, opt);
		cd_opt_dir(data, opt);
	}
	else
		write(1, "Args not valid.\n", 16);
	free_2d(opt);
}
