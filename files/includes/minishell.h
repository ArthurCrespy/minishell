/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:31:36 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 12:31:36 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MALLOC_ERROR 1
# define TCGETATTR_ERROR 2

# define BUFFER_SIZE 1024

# define USER "acrespy"

typedef struct s_command
{
	char				*cmd;
	struct s_command	*prev;
	struct s_command	*next;
}				t_command;

typedef struct s_data
{
	t_command	*history;
	char		**command;
	char		**env;
}				t_data;

// ------- CMD PARSING ------ //
void	command_parsing(t_data *data, char *command);

// ------ CMD REPLACE ----- //
char	*ft_char_replace(t_data *data, char *command, int c);
char	*ft_operators_replace(t_data *data, char *command);
char	*ft_quotes_replace(t_data *data, char *command);

// ------- ENV REPLACE ------ //
char	*ft_env_replace(t_data *data, char *command);
void	env_save(t_data *data, int argc, char **argv, char **envp);

// ---------- FREE ---------- //
void	ft_exit(t_data *data, int status, char *msg);
void	ft_free_tab(char **tab);
void	ft_free(t_data data);

// ------ PRPT HISTORY ------ //
void	history_add(t_data *data, char *cmd);
void	history_free(t_data *data);

// -------- PRPT KEYS ------- //
void	key_processing(t_data *data, int key);

// ------- PRPT LAUNCH ------ //
void	prompt_launch(t_data *data);

// ------- UTILS ATOI ------- //
char	*ft_itoa(int n);

// -------- UTILS GNL ------- //
char	*get_next_line(int fd);

// ------- UTILS SPLIT ------ //
char	**ft_strsplit(t_data data, char const *s, char c);

// -------- UTILS STR ------- //
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(t_data data, char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

// ------ UTILS STR MEM ----- //
char	*ft_strdup(t_data data, char *str);
char	*ft_calloc(size_t nmemb, size_t size);

// -------- UTILS STR ------- //
int		ft_tablen(char **tab);
int		ft_tabchr(char **tab, const char *str);
#endif
