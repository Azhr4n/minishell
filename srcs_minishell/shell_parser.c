/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 12:14:52 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 12:15:02 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

#include <stdio.h>

void		parsing_precut(t_data *data, char *str)
{
	char	**commands;
	int		length;
	int		i;

	commands = split_char(str, ';');
	length = 0;
	while (commands[length])
		length++;
	data->btree = (t_btree **)malloc(sizeof(t_btree *) * (length + 1));
	data->btree[length] = 0;
	i = 0;
	while (data->btree[i])
	{
		data->btree[i] = 0;
		i++;
	}
	i = 0;
	while (commands[i])
	{
		parsing(data, commands[i], i);
		i++;
	}
	free_2d(commands);
}

static int	next_separator(char *str, char separator[3])
{
	static char	*sep[] = {"&&", 0};
	int			i;

	szero(separator, 3);
	while (*str)
	{
		i = 0;
		while (sep[i])
		{
			if (!ft_strncmp(str, sep[i], ft_strlen(sep[i])))
			{
				ft_strcpy(separator, sep[i]);
				return (1);
			}
			i++;
		}
		str++;
	}
	return (0);
}

// In parsing

void		parsing(t_data *data, char *str, int btree_index)
{
	char	separator[3];
	char	**tab;
	t_btree	*btree;

	btree = rightmost_node(data->btree[btree_index]);
	if (next_separator(str, separator))
	{
		tab = cut_string(str, separator);
		btree = create_elem_right(btree, trim(separator), SEPARATOR);
		if (!data->btree[btree_index])
			data->btree[btree_index] = btree;
		btree->left = create_elem(trim(tab[0]), COMMAND);
		parsing(data, tab[1], btree_index);
		free_2d(tab);
	}
	else
	{
		if (!data->btree[btree_index])
			data->btree[btree_index] = create_elem(trim(str), COMMAND);
		else
			btree->right = create_elem(trim(str), COMMAND);
	}
}
