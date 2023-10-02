/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:03:52 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 19:16:53 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_UTILS_H
# define MINISHELL_CMD_UTILS_H

// ------------ ENV ------------ //
char	*ft_env_replace(t_data *data, t_parsing *parsing);

// ------------ EXEC ----------- //

// ---------- PARSING ---------- //
char	*ft_char_replace(t_data *data, t_parsing *parsing, int c);
char	*ft_operators_replace(t_data *data, t_parsing *parsing);
char	*ft_quotes_replace(t_data *data, t_parsing *parsing, char c);
void	ft_operators_separate(t_parsing *parsing);
void	ft_quotes_check(t_parsing *parsing);
int		ft_quotes_closed(const char *str);
int		ft_quotes_enclosed(t_parsing *parsing, int open, int i);
t_exec	*ft_exec_node_create(t_data *data);
t_exec	*ft_exec_node_null(t_exec *exec);
void	ft_exec_token_parser(t_data *data, t_exec *exec, int *i);

// ----------- UTILS ----------- //
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_strsplit(t_data *data, char const *s, char c);
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int i);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(t_data *data, char *str);
char	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(t_data *data, char const *s, unsigned int start, size_t len);
int		ft_tablen(char **tab);
int		ft_tabslen(char **tab);
int		ft_tabchr(char **tab, const char *str);
int		ft_tabcount(char **tab, const char c);
int		ft_istoken(char *str);
int		ft_isalpha(char c);
int		ft_isdigit(char c);

#endif
