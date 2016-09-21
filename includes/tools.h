/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:30:44 by pivanovi          #+#    #+#             */
/*   Updated: 2015/12/03 15:30:44 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

void	ft_putstr(char *str);
void	ft_putendl(char *str);
void	szero(char *str, int len);
void	free_2d(char **tab);

int		ft_strlen(char *str);
int		ft_strlen2d(char **tab);
int		strlen_char(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		strcmp_char(char *s1, char *s2, char c);
int		is_char(char *s1, char c);

char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int n);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, int n);
char	*ft_strcat(char *dest, char *src);
char	*trim(char *str);
char	*strcpy_char(char *dest, char *src, char c);
char	*strcat_char(char *dest, char *src, char c);

char	**split_char(char *str, char c);
char	**split_space(char *str);
char	**cut_string(char *str, char *str2);

#endif
