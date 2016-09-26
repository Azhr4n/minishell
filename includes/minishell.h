/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:30:51 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 15:30:51 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFSIZE 2048

enum
{
	SEPARATOR,
	COMMAND,
	NB_TYPE
};

enum
{
	ECHO_N,
	ECHO_E,
	NB_ECHO_OPT
};

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			*data;
	int				type;
}					t_btree;

typedef struct		s_data
{
	char			**env;
	t_btree			**btree;
}					t_data;

void				parsing_precut(t_data *data, char *str);
void				parsing(t_data *data, char *str, int btree_index);

t_btree				*create_elem(char *data, int type);
t_btree				*create_elem_right(t_btree *btree, char *data, int type);
t_btree				*rightmost_node(t_btree *btree);
void				free_btree(t_btree *btree);

void				exec_command(t_data *data,
	t_btree *btree, char buffer[BUFFSIZE + 1]);
int					split_paths(t_data *data, char ***paths);
void				search_then_exec(t_data *data, t_btree *btree);
void				exec_separator(t_data *data, t_btree *btree);
void				execute_command(t_data *data);

int					call_builtin(t_data *data, t_btree *btree);

void				remove_to_env(t_data *data, int index);
void				builtin_unsetenv(t_data *data, t_btree *btree);

void				add_to_env(t_data *data, char **opt, int i);
void				builtin_setenv(t_data *data, t_btree *btree);

void				builtin_env(t_data *data, t_btree *btree);

void				builtin_cd(t_data *data, t_btree *btree);

int					builtin_echo(t_btree *btree);

void				set_oldpwd(t_data *data, char *new_value);
void				set_pwd(t_data *data);

int					get_index_env(char **env, char *str);

void				realloc_env(t_data *data, char *value);

void				change_dir(t_data *data, char *path);

void				main_loop(t_data *data);

int					strstrplus(char *s1, char *s2);

#endif
