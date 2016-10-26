/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_next.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 14:30:24 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 14:30:24 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	cd_opt_dir(t_holder *holder)
{
	DIR		*fd;

	if (ft_strcmp(holder->data[1], "-") && ft_strncmp(holder->data[1], "~", 1))
	{
		fd = opendir(holder->data[1]);
		if (fd)
		{
			change_dir(holder, holder->data[1], 256);
			closedir(fd);
		}
		else
			ft_putstr("You don't have the rights to do this.\n");
	}
}

void	cd_opt_tild(t_holder *holder)
{
	DIR		*fd;
	char	*path;
	int		index;

	if (!ft_strncmp(holder->data[1], "~", 1))
	{
		if ((index = env_index(holder->env, "HOME")) != -1)
		{
			if ((path = (char *)malloc(sizeof(char) * (5 + L(holder->env[index])
				+ L(holder->data[1])))) == NULL)
				return ;
			path = ft_strcpy(path, holder->env[index] + ft_strlen("HOME="));
			path = ft_strcat(path, holder->data[1] + 1);
			if ((fd = opendir(path)))
			{
				change_dir(holder, path, 256);
				closedir(fd);
			}
			else
				write(1, "Path inexistant.\n", 17);
			free(path);
		}
		else
			ft_putstr("No HOME in env.\n");
	}
}

void	cd_opt_minus(t_holder *holder)
{
	DIR		*fd;
	char	*path;
	int		index;

	if (!ft_strcmp(holder->data[1], "-"))
	{
		if ((index = env_index(holder->env, "OLDPWD")) != -1)
		{
			path = holder->env[index] + ft_strlen("OLDPWD=");
			if ((fd = opendir(path)))
			{
				change_dir(holder, path, 256);
				closedir(fd);
			}
			else
				ft_putstr("You don't have the rights to do that.\n");
		}
		else
			ft_putstr("No oldpwd in env.\n");
	}
}
