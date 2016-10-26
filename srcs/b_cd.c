/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 13:31:00 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 13:31:00 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

static void	cd_no_opt2(t_holder *holder, DIR *fd, char *path, int size)
{
	char	buff[size + 1];
	char	*ret;

	if (fd)
	{
		ft_bzero(buff, sizeof(char) * (size + 1));
		if ((ret = getcwd(buff, size)) == NULL)
		{
			cd_no_opt2(holder, fd, path, size * 2);
			return ;
		}
		if ((chdir(path)) == -1)
		{
			write(2, "Chdir failed.\n", 14);
			return ;
		}
		set_oldpwd(holder, buff);
		set_pwd(holder, 256);
		closedir(fd);
	}
	else
		write(1, "You don't have the rights to do that.\n", 38);
}

static void	cd_no_opt(t_holder *holder)
{
	DIR		*fd;
	int		index;
	char	*path;

	index = env_index(holder->env, "HOME");
	if (index != -1)
	{
		path = holder->env[index] + ft_strlen("HOME=");
		fd = opendir(path);
		cd_no_opt2(holder, fd, path, 256);
	}
	else
		ft_putstr("No HOME in env.\n");
}

void		b_cd(t_holder *holder)
{
	int		size;

	size = 0;
	while (holder->data[size])
		size++;
	if (size == 1)
		cd_no_opt(holder);
	else if (size == 2)
	{
		cd_opt_minus(holder);
		cd_opt_tild(holder);
		cd_opt_dir(holder);
	}
	else
		ft_putstr("Arguments not valids.\n");
}
