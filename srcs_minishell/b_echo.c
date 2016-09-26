

#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "tools.h"

#include <stdio.h>

void	echo_no_opt(char *data)
{
	while (*data)
	{
		if (*data != '\'' && *data != '\"')
			write(1, data, 1);
		data++;
	}
	write(1, "\n", 1);
}

int		which_opt(char *data, int *options)
{
	int		i;

	if (data[0] == '-')
	{
		i = 0;
		while (data[++i])
		{
			if (data[i] == 'n')
				options[ECHO_N] = 1;
			else if (data[i] == 'e')
				options[ECHO_E] = 1;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int		builtin_echo(t_btree *btree)
{
	char	**opt;
	int		size;
	int		*options;

	if ((options = (int *)malloc(sizeof(int) * NB_ECHO_OPT)) == NULL)
	{
		ft_putendl("Echo malloc failed.");
		return (1);
	}
	ft_bzero(options, NB_ECHO_OPT * sizeof(int));
	size = 0;
	opt = split_char(btree->data, ' ');
	while (opt[size])
		size++;
	if (size == 1)
		write(1, "\n", 1);
	else
	{
		if (!which_opt(opt[1], options))
			echo_no_opt(btree->data + 5);
	}
	free_2d(opt);
	return (1);
}