/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:03:52 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 21:17:40 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_UTILS_H
# define MINISHELL_CMD_UTILS_H

// ------ CMD REPLACE ----- //
char	*ft_char_replace(t_data *data, char *command, int c);
char	*ft_operators_replace(t_data *data, char *command);
char	*ft_quotes_replace(t_data *data, char *command, char c);

// ------- ENV REPLACE ------ //
char	*ft_env_replace(t_data *data, char *command);

// ---------- PATH ---------- //
char	*ft_path(t_data *data);
char	*ft_device(t_data *data);

// ------- UTILS ATOI ------- //
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

// -------- UTILS GNL ------- //
char	*get_next_line(int fd);

// ------- UTILS SPLIT ------ //
char	**ft_strsplit(t_data data, char const *s, char c);

// -------- UTILS STR ------- //
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

// ------ UTILS STR MEM ----- //
char	*ft_strdup(t_data data, char *str);
char	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(t_data data, char const *s, unsigned int start, size_t len);

// -------- UTILS TAB ------- //
int		ft_tablen(char **tab);
int		ft_tabchr(char **tab, const char *str);
int		ft_tabcount(char **tab, const char c);

#endif
