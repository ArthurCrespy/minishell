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
# define TERMIOS_ERROR 2

typedef struct s_history
{
	int					id;
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

typedef struct s_data
{
	t_history	*history;
}				t_data;

// ---------- FREE ---------- //
void    ft_exit(t_data *data, int status, char *msg);
void	ft_free(t_data data);

// ------ PRPT HISTORY ------ //
void	history_add(t_data *data, char *cmd);
void	history_print(t_data *data);
void	history_free(t_data *data);

// -------- PRPT KEYS ------- //
void	key_processing(t_data *data, int key);

// ------- PRPT LAUNCH ------ //
void	prompt_launch(t_data *data);

// -------- UTILS STR ------- //
size_t	ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(t_data data, const char *str);

#endif
