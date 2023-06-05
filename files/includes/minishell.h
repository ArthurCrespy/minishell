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
# define ENV_ERROR 3

# define BUFFER_SIZE 1024

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
	int			return_value;
}				t_data;

// ------- CMD PARSING ------ //
void	command_parsing(t_data *data, char *command);

// -------- ENV SAVE -------- //
void	env_save(t_data *data, int argc, char **argv, char **envp);

// ------- ENV MODIFY ------- //
void	env_update(t_data *data, char *name, char *value);
void	env_add(t_data *data, char *name, char *value);
void	env_delete(t_data *data, char *name);

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

# include "./minishell_utils.h"

#endif