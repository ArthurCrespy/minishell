/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:59:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/13 11:55:25 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_H
# define MINISHELL_CMD_H

// ------- CMD PARSING ------ //
void	command_parsing(t_data *data, char *command);

// ------- CMD PROCESS ------ //
void	command_processing(t_data *data);

// -------- ENV SAVE -------- //
void	env_save(t_data *data, int argc, char **argv, char **envp);

// ------- ENV MODIFY ------- //
void	env_update(t_data *data, char *name, char *value);
void	env_add(t_data *data, char *name, char *value);
void	env_delete(t_data *data, char *name);

// ---------- FREE ---------- //
void	ft_exit(t_data *data, int status, char *msg);
void	ft_free_tab(char **tab);
void	ft_free(t_data *data);

// ------ PRPT HISTORY ------ //
void	history_add(t_data *data, char *cmd);
void	history_free(t_data *data);

// -------- PRPT KEYS ------- //
void	key_processing(t_data *data, int key);

// ------- PRPT LAUNCH ------ //
void	prompt_launch(t_data *data);

// ------- SIG HANDLE ------- //
void	signal_handle(t_data *data);

#endif
