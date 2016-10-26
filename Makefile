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
CFLAGS = -Wall -Wextra -Werror

SRCS_MINISHELL =	srcs/env.c						\
					srcs/b_cd.c						\
					srcs/b_echo.c					\
					srcs/cd_next.c					\
					srcs/set_pwd.c					\
					srcs/b_setenv.c					\
					srcs/redirect.c					\
					srcs/minishell.c				\
					srcs/read_entry.c				\
					srcs/b_unsetenv.c				\
					srcs/shell_split.c				\
					srcs/exec_commands.c

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
LIBFT = libft/libft.a

CFLAGS += -I./includes -I./libft

all: minishell

minishell: $(OBJS_MINISHELL)
	cd libft && make
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS_MINISHELL) -o $@

clean:
	/bin/rm -f $(OBJS_MINISHELL) && cd libft && make clean

fclean: clean
	/bin/rm -f minishell && cd libft && make fclean

re: fclean all

