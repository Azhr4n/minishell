/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:48:39 by pivanovi          #+#    #+#             */
/*   Updated: 2016/10/20 12:48:40 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFSIZE 1024

# define L ft_strlen

enum
{
	NO_Q,
	SIMPLE_Q,
	DUAL_Q
};

enum
{
	B_EXIT,
	B_ECHO,
	B_CD,
	B_ENV,
	B_SETENV,
	B_UNSETENV,
	NB_BUILTINS
};

typedef struct		s_data
{
	char			**data;
	struct s_data	*next;
}					t_data;

typedef struct		s_holder
{
	char			**data;
	char			**env;
	void			(*b_func[NB_BUILTINS])(struct s_holder *);
}					t_holder;

char				*reading_standard(void);
void				parse(char *data);

void				redirect(t_holder *holder);
void				process(t_holder *holder);

char				**shell_split(char *str);
void				free_2d(char **array);

void				realloc_env(t_holder *holder, char *value);
void				cpy_env(t_holder *holder, char **env);
int					env_index(char **env, char *name);

void				set_oldpwd(t_holder *holder, char *new_value);
void				set_pwd(t_holder *holder, int size);
void				change_dir(t_holder *holder, char *path, int size);

void				b_cd(t_holder *holder);
void				cd_opt_dir(t_holder *holder);
void				cd_opt_tild(t_holder *holder);
void				cd_opt_minus(t_holder *holder);

void				b_env(t_holder *holder);
void				b_setenv(t_holder *holder);
void				b_unsetenv(t_holder *holder);

void				b_echo(t_holder *holder);

#endif
