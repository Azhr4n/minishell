/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 13:44:59 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/26 13:44:59 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

void	set_oldpwd(t_holder *holder, char *new_value)
{
	char	*str;
	int		index;
	int		len;

	len = 7 + ft_strlen(new_value);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	ft_strcpy(str, "OLDPWD=");
	ft_strcat(str, new_value);
	if ((index = env_index(holder->env, "OLDPWD")) != -1)
	{
		free(holder->env[index]);
		holder->env[index] = ft_strdup(str);
	}
	else
		realloc_env(holder, str);
	free(str);
}

void	set_pwd(t_holder *holder, int size)
{
	char	buff[size];
	char	*str;
	int		index;
	int		len;

	ft_bzero(buff, sizeof(char) * (size + 1));
	if ((str = getcwd(buff, size)) == NULL)
	{
		set_pwd(holder, size * 2);
		return ;
	}
	len = 4 + ft_strlen(buff);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	ft_strcpy(str, "PWD=");
	ft_strcat(str, buff);
	if ((index = env_index(holder->env, "PWD")) != -1)
	{
		free(holder->env[index]);
		holder->env[index] = ft_strdup(str);
	}
	else
		realloc_env(holder, str);
	free(str);
}

void	change_dir(t_holder *holder, char *path, int size)
{
	char	path_pwd[size + 1];

	ft_bzero(path_pwd, size + 1);
	if ((getcwd(path_pwd, size)) == NULL)
		change_dir(holder, path, size * 2);
	else
	{
		if ((chdir(path)) != -1)
		{
			set_oldpwd(holder, path_pwd);
			set_pwd(holder, size);
		}
		else
			ft_putstr("Chdir failed.\n");
	}
}
