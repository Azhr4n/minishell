/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:16:57 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 15:16:57 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

int		call_builtin(t_data *data, t_btree *btree)
{
	if (!strcmp_char(btree->data, "exit", ' '))
		exit(0);
	else if (!strcmp_char(btree->data, "cd", ' '))
	{
		builtin_cd(data, btree);
		return (1);
	}
	else if (!strcmp_char(btree->data, "env", ' '))
	{
		builtin_env(data, btree);
		return (1);
	}
	else if (!strcmp_char(btree->data, "setenv", ' '))
	{
		builtin_setenv(data, btree);
		return (1);
	}
	else if (!strcmp_char(btree->data, "unsetenv", ' '))
	{
		builtin_unsetenv(data, btree);
		return (1);
	}
	return (0);
}
