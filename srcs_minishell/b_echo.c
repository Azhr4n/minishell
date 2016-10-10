/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:37:32 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/27 12:37:32 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

#include <stdio.h>

int		get_index(char c)
{
	static char	tab[NB_BS_OPT] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\'};
	int			i;

	i = -1;
	while (++i < NB_BS_OPT)
	{
		if (tab[i] == c)
			return (i);
	}
	return (-1);
}

int		starting_quote(char c, int current_state)
{
	if (c == '\"' && !current_state)
		return (DUAL_Q);
	else if (c == '\'' && !current_state)
		return (SIMPLE_Q);
	else if ((c == '\"' && current_state == DUAL_Q)
		|| (c == '\'' && current_state == SIMPLE_Q))
		return (NO_Q);
	return (current_state);
}

void	print_echo_3(char **data, int *options, int g)
{
	static char	tab[NB_BS_OPT] = {'\a', '\b', '\f', '\n',
		'\r', '\t', '\v', '\\'};
	int		index;

	if ((**data != '\'' && **data != '\"') || (**data == '\'' && g != SIMPLE_Q)
		|| (**data == '\"' && g != DUAL_Q))
	{
		if (**data == '\\' && g && options[ECHO_E])
		{
			if ((index = get_index(*(*data + 1))) != -1)
				write(1, &tab[index], 1);
			else
				write(1, *data, 1);
			(*data)++;
		}
		else
			write(1, *data, 1);
	}
}

void	print_echo_2(char *data, int *options, int quote)
{
	int		old_g;
	int		g;

	g = quote;
	while (*data)
	{
		old_g = g;
		g = starting_quote(*data, g);
		if (old_g && !g)
			print_echo_3(&data, options, old_g);
		else
			print_echo_3(&data, options, g);
		data++;
	}
}

void	print_echo(t_echo *echo, int *options)
{
	int		quote;
	int		i;
	t_echo	*ptr;

	quote = 0;
	while(echo != NULL)
	{
		i = -1;
		print_echo_2(echo->buff, options, quote);
		while (echo->buff[++i])
			quote = starting_quote(echo->buff[i], quote);
		ptr = echo;
		echo = echo->next;
		free(ptr);
	}
}

t_echo	*chunking(char *data, t_echo *echo)
{
	char	buff[BUFFSIZE + 1];

	while (ft_strlen(data) > BUFFSIZE)
	{
		ft_strncpy(buff, data, BUFFSIZE + 1);
		add_echo_at_end(&echo, buff);
		data += BUFFSIZE;
	}
	add_echo_at_end(&echo, data);
	return (echo);
}

void	echo(char *data, int *options)
{
	t_echo		*echo;
	char		buffer[BUFFSIZE + 1];
	int			end;
	int			ret;
	int			i;
	int			quote;

	echo = NULL;
	i = -1;
	quote = NO_Q;
	while (data[++i])
		quote = starting_quote(data[i], quote);
	echo = chunking(data, echo);
	if (quote != NO_Q)
	{
		add_echo_at_end(&echo, "\n");
		end = 0;
		while (!end)
		{
			write(1, ">", 1);
			if ((ret = read(0, buffer, BUFFSIZE)) == -1)
				return ;
			buffer[ret] = 0;
			i = -1;
			while (buffer[++i])
			{
				if ((buffer[i] == '\"' && quote == DUAL_Q) 
					|| (buffer[i] == '\'' && quote == SIMPLE_Q))
				{
					end = 1;
					buffer[ret - 1] = 0;
				}
			}
			add_echo_at_end(&echo, buffer);
		}
	}
	print_echo(echo, options);
}

char	*which_opt(char *data, int *options)
{
	char	*ptr;

	while (*data)
	{
		ptr = data;
		while (*data == '-' || *data == 'e' || *data == 'n')
		{
			if (*data == 'e')
				options[ECHO_E] = 1;
			else if (*data == 'n')
				options[ECHO_N] = 1;
			data++;
			if (*data == '-')
				return (ptr);
		}
		if (*data == ' ' || *data == '\t')
		{
			data++;
			ptr = data;
		}
		else
			return (ptr);
	}
	return (data);
}

int		builtin_echo(t_btree *btree)
{
	char	**opt;
	char	*ptr;
	int		size;
	int		*options;

	if ((options = (int *)malloc(sizeof(int) * NB_ECHO_OPT)) == NULL)
		return (1);
	ft_bzero(options, NB_ECHO_OPT * sizeof(int));
	size = 0;
	opt = split_char(btree->data, ' ');
	while (opt[size])
		size++;
	if (size == 1)
		write(1, "\n", 1);
	else
	{
		ptr = which_opt(btree->data + 5, options);
		echo(ptr, options);
		if (!options[ECHO_N])
			write(1, "\n", 1);
	}
	free(options);
	free_2d(opt);
	return (1);
}