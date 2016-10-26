/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:20:23 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/27 15:20:24 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

t_echo	*new_echo_elem(char *str)
{
	t_echo	*ret;

	if ((ret = (t_echo *)malloc(sizeof(t_echo))) == NULL)
		return (NULL);
	bzero(ret->buff, BUFFSIZE * sizeof(char));
	ret->buff = ft_strcpy(ret->buff, str);
	ret->next = NULL;
	return (ret);
}

void	add_echo_at_end(t_echo *echo, char *str)
{
	t_echo	*ptr;

	if (echo == NULL)
		echo = new_echo_elem(str);
	ptr = echo;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_echo_elem(str);
}