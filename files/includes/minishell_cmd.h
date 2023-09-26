/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:59:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/25 20:37:05 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_H
# define MINISHELL_CMD_H

// -------- EXEC ------------//
void	exec(t_data *data);
void	launch_exec(t_data *data, t_exec *exec);
int		set_in_and_out(t_data *data, t_exec *exec, t_pipex *pipex);
int		set_command(t_data *data, t_exec *exec, t_pipex *pipex);
int		here_doc(t_exec *exec);
char	*find_path_cmd(t_data *data, t_exec *exec, t_pipex *pipex);

// ------- BUILTINS -------- //
int		ft_ft_exit(t_data *data, t_exec *exec);
void	ft_pwd(t_data *data);
int		ft_cd(t_data *data, t_exec *exec);
int		ft_echo(t_data *data, t_exec *exec);
void	find_cmd(t_data *data, t_exec *exec);
void	ft_env(t_data *data);
int		ft_export(t_data *data, t_exec *exec);
void	ft_unset(t_data *data, t_exec *exec);

// ------- CMD PARSING ------ //
void	command_parsing(t_data *data, char *command);
t_exec	ft_parse(t_data *data);

// ------- CMD PROCESS ------ //
void	command_processing(t_data *data);

// -------- ENV UTILS ------- //
void	env_save(t_data *data, int argc, char **argv, char **envp);
char	*env_return(t_data *data, char *name);

// ------- ENV MODIFY ------- //
void	env_update(t_data *data, char *name, char *value);
void	env_add(t_data *data, char *name, char *value);
void	env_delete(t_data *data, char *name);

// ---------- FREE ---------- //
void	ft_exit(t_data *data, int code, int error, char *origin);
void	ft_free_tab(char **tab);
void	ft_free_exec(t_exec **exec);
void	ft_free(t_data *data);

// ---------- PRINT --------- //
void	print_exec(t_data *data);

// ------ PRPT HISTORY ------ //
void	history_add(t_data *data, char *cmd);
void	history_free(t_data *data);

// -------- PRPT KEYS ------- //
void	key_processing(t_data *data, int key);

// ------- PRPT LAUNCH ------ //
void	prompt_launch(t_data *data);

// ------- SIG HANDLE ------- //
int		signal_status(int status, int set);
void	signal_handle(t_data *data);

#endif
