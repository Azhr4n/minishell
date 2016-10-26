/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 14:22:02 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/20 14:22:03 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

#include "minishell.h"

static int	checking_quotes(char *str)
{
	static int	actual_quoting = 0;

	while (*str)
	{
		if (*str == '\'' && !actual_quoting)
			actual_quoting = SIMPLE_Q;
		else if (*str == '\'' && actual_quoting == SIMPLE_Q)
			actual_quoting = 0;
		else if (*str == '\"' && !actual_quoting)
			actual_quoting = DUAL_Q;
		else if (*str == '\"' && actual_quoting == DUAL_Q)
			actual_quoting = 0;
		str++;
	}
	return (actual_quoting);
}

static char	*create_str(char *src, char *buffer)
{
	char	*new_str;

	if (src == NULL)
	{
		if ((new_str = ft_strdup(buffer)) == NULL)
			exit(-1);
	}
	else
	{
		free(src);
		if ((new_str = (char *)malloc(ft_strlen(src)
			+ ft_strlen(buffer) + 1)) == NULL)
			exit(-1);
		new_str = ft_strcpy(new_str, src);
		new_str = ft_strcat(new_str, buffer);
	}
	return (new_str);
}

static void	show_prompt(int quote)
{
	if (!quote)
		ft_putstr("$> ");
	else if (quote == SIMPLE_Q)
		ft_putstr("quote> ");
	else if (quote == DUAL_Q)
		ft_putstr("dquote> ");
}

char		*reading_standard(void)
{
	char	buff[BUFFSIZE];
	char	*str;
	int		quote;
	int		quit;
	int		ret;

	quote = 0;
	quit = 0;
	str = NULL;
	while (!quit)
	{
		show_prompt(quote);
		ret = read(0, buff, BUFFSIZE);
		buff[ret] = 0;
		quote = checking_quotes(buff);
		if (!quote && ret < BUFFSIZE)
		{
			buff[ret - 1] = 0;
			quit = 1;
		}
		else if (ret < 0)
			exit(-1);
		str = create_str(str, buff);
	}
	return (str);
}
