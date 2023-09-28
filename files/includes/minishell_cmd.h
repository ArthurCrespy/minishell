/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:59:15 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/27 16:04:05 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CMD_H
# define MINISHELL_CMD_H

// ---------- BUILTINS --------- //
int		builtin_cd(t_data *data, t_exec *exec);
int		builtin_echo(t_data *data, t_exec *exec);
void	builtin_env(t_data *data);
int		builtin_exit(t_data *data, t_exec *exec);
int		builtin_export(t_data *data, t_exec *exec);
void	builtin_pwd(t_data *data);
void	builtin_unset(t_data *data, t_exec *exec);
int		check_builtin(t_data *data, t_exec *exec);


// ----------- DEVICE ---------- //
char	*device_find(t_data *data);

// ------------ ENV ------------ //
void	env_update(t_data *data, char *name, char *value);
void	env_add(t_data *data, char *name, char *value);
void	env_delete(t_data *data, char *name);
void	env_save(t_data *data, int argc, char **argv, char **envp);
char	*env_return(t_data *data, char *name);

// ------------ EXEC ----------- //
void	exec_run(t_data *data);
void	exec_data_set(t_data *data, t_exec *exec);
void	exec_child(t_data *data, t_exec *exec, t_pipex *pipex);
int		exec_builtin(t_data *data, t_exec *exec);
int		heredoc(t_exec *exec);
int		set_pipe(t_data *data, t_exec *exec, t_pipex *pipex);
int		exec_launch(t_data *data, t_exec *exec, t_pipex *pipex);

// ------------ EXIT ----------- //
void	ft_exit(t_data *data, int code, int error, char *origin);

// ------------ FREE ----------- //
void	ft_free_tab(char **tab);
void	ft_free_exec(t_data *data);
void	ft_free(t_data *data);

// ---------- PARSING ---------- //
void	parsing_input(t_data *data, char *command);

// ------------ PATH ----------- //
char	*path_find(t_data *data);
char	*path_find_cmd(t_data *data, t_exec *exec, t_pipex *pipex);

// ----------- PROMPT ---------- //
void	history_add(t_data *data, char *cmd);
void	history_free(t_data *data);
void	key_processing(t_data *data, int key);
void	prompt_run(t_data *data);
char	*prompt_device_info(t_data *data);

// ----------- SIGNAL ---------- //
int		signal_status(int status, int set);
void	signal_handle(t_data *data);

#endif
