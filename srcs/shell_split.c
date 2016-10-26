/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 12:19:06 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/25 12:19:07 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

#include <stdio.h>

static int	get_quote(char c)
{
	static int	quote = 0;

	if (!quote && c == '\'')
		quote = SIMPLE_Q;
	else if (quote == SIMPLE_Q && c == '\'')
		quote = 0;
	else if (!quote && c == '\"')
		quote = DUAL_Q;
	else if (quote == DUAL_Q && c == '\"')
		quote = 0;
	return (quote);
}

static int	nb_words(char *str)
{
	int		count;
	int		flag;
	int		quote;

	flag = 0;
	count = 0;
	while (*str)
	{
		quote = get_quote(*str);
		if (*str != ' ' && *str != '\t' && !flag)
		{
			count++;
			flag = 1;
		}
		else if ((*str == ' ' || *str == '\t') && !quote)
			flag = 0;
		str++;
	}
	return (count);
}

static int	nb_letters(char *str)
{
	int		count;
	int		quote;

	count = 0;
	quote = get_quote(*str);
	while (str[count] && ((str[count] != ' ' && str[count] != '\t') || quote))
	{
		count++;
		quote = get_quote(str[count]);
	}
	return (count);
}

static char *split(char **str)
{
	char	*ret;
	int		len;
	int		quote;

	if ((quote = get_quote(**str)) > 0)
		(*str)++;
	len = nb_letters(*str);
	if (quote)
		len--;
	if ((ret = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ret[len] = 0;
	ret = ft_strncpy(ret, *str, len); 
	(*str) += len;
	if (quote)
		(*str)++;
	return (ret);
}

char		**shell_split(char *str)
{
	char	**array;
	int		len;
	int		i;

	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	len = nb_words(str);
	if (!len)
		return (NULL);
	if ((array = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	array[len] = 0;
	i = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		array[i] = split(&str);
		i++;
	}
	return (array);
}
