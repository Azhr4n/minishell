/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:50:49 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:50:50 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"
#include "tools.h"

void	change_dir(t_data *data, char *path)
{
	char	path_pwd[BUFFSIZE + 1];

	szero(path_pwd, BUFFSIZE + 1);
	if ((getcwd(path_pwd, BUFFSIZE)) == NULL)
		write(2, "Error.\n", 7);
	else
	{
		if ((chdir(path)) != -1)
		{
			set_oldpwd(data, path_pwd);
			set_pwd(data);
		}
		else
			write(2, "Chdir failed.\n", 14);
	}
}
