/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 13:00:47 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/09 13:00:48 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

t_btree		*create_elem(char *data, int type)
{
	t_btree		*ret;

	ret = (t_btree *)malloc(sizeof(t_btree));
	if (!ret)
		return (0);
	ret->left = 0;
	ret->right = 0;
	ret->data = data;
	ret->type = type;
	return (ret);
}

t_btree		*create_elem_right(t_btree *btree, char *data, int type)
{
	if (!btree)
		return (create_elem(data, type));
	btree->right = create_elem(data, type);
	return (btree->right);
}

t_btree		*rightmost_node(t_btree *btree)
{
	if (!btree)
		return (0);
	while (btree->right)
		btree = btree->right;
	return (btree);
}

void		free_btree(t_btree *btree)
{
	if (btree->left)
		free_btree(btree->left);
	if (btree->right)
		free_btree(btree->right);
	free(btree->data);
	free(btree);
	btree = 0;
}
