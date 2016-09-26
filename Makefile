# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 15:30:51 by pivanovi          #+#    #+#              #
#    Updated: 2016/01/07 17:35:05 by pivanovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TOOLS =				srcs/split_char.c						\
					srcs/split_space.c						\
					srcs/cut_string.c						\
					srcs/strings_cmp.c						\
					srcs/string_print.c						\
					srcs/strings_ope.c						\
					srcs/ft_trim.c							\
					srcs/ft_strlen.c						\
					srcs/free_2d.c							\
					srcs/str_char.c							\
					srcs/szero.c

SRCS_MINISHELL =	srcs_minishell/minishell.c				\
					srcs_minishell/shell_parser.c			\
					srcs_minishell/btree_functions.c		\
					srcs_minishell/b_cd.c					\
					srcs_minishell/b_env.c					\
					srcs_minishell/b_echo.c					\
					srcs_minishell/b_setenv.c				\
					srcs_minishell/b_unsetenv.c				\
					srcs_minishell/builtins_exec.c			\
					srcs_minishell/exec_commands.c			\
					srcs_minishell/get_index_env.c			\
					srcs_minishell/realloc_env.c			\
					srcs_minishell/set_pwd.c				\
					srcs_minishell/change_dir.c



OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
OBJS_TOOLS = $(TOOLS:.c=.o)

CFLAGS += -I./includes

all: minishell

minishell: $(OBJS_MINISHELL) $(OBJS_TOOLS)
	$(CC) $(CFLAGS) $(OBJS_MINISHELL) $(OBJS_TOOLS) -o $@

clean:
	/bin/rm -f $(OBJS_MINISHELL) && /bin/rm -f $(OBJS_TOOLS)

fclean: clean
	/bin/rm -f minishell

re: fclean all

