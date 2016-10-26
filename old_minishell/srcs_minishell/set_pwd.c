/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:25:34 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:25:35 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"
#include "tools.h"

void	set_oldpwd(t_data *data, char *new_value)
{
	char	*str;
	int		index;
	int		len;

	len = 7 + ft_strlen(new_value);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	ft_strcpy(str, "OLDPWD=");
	ft_strcat(str, new_value);
	if ((index = get_index_env(data->env, "OLDPWD")) != -1)
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(str);
	}
	else
		realloc_env(data, str);
	free(str);
}

void	set_pwd(t_data *data)
{
	char	buff[BUFFSIZE + 1];
	char	*str;
	int		index;
	int		len;

	szero(buff, BUFFSIZE + 1);
	str = getcwd(buff, BUFFSIZE);
	if (str != NULL)
	{
		len = 4 + ft_strlen(buff);
		str = (char *)malloc(sizeof(char) * (len + 1));
		str[len] = 0;
		ft_strcpy(str, "PWD=");
		ft_strcat(str, buff);
		if ((index = get_index_env(data->env, "PWD")) != -1)
		{
			free(data->env[index]);
			data->env[index] = ft_strdup(str);
		}
		else
			realloc_env(data, str);
		free(str);
	}
}
