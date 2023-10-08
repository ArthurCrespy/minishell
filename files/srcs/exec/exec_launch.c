/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 00:51:59 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fork, set the pipes, and call the function to launch the exec in the child
int	exec_launch(t_data *data, t_exec *exec)
{
	pid_t	pid;

	signal_handle(data, 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	exec->pid = pid;
	exec->is_pid = true;
	if (pid == 0)
		exec_child(data, exec);
	if (exec->fdin != STDIN_FILENO)
		close(exec->fdin);
	if (data->pipes_nb != 0)
		close(exec->pipefd[1]);
	if (exec->id_exec != 0)
		close(data->exec[exec->id_exec - 1]->pipefd[0]);
	if (data->pipes_nb)
		data->pipes_nb--;
	if (exec->delimiter_nb)
		unlink(".heredoc");
	if (check_builtin(data, exec) == 0)
	{
		free(exec->cmd_exec);
		free(exec->cmd_path);
		exec->cmd_exec = NULL;
		exec->cmd_path = NULL;
	}
	if (exec->delimiter_nb)
		waitpid(-1, NULL, 0);
	return (0);
}

// Set the pipes then launch the execve/builtins in the child
void	exec_child(t_data *data, t_exec *exec)
{
	change_fdin(exec);
	if (data->pipes_nb != 0)
		close(exec->pipefd[0]);
	change_fdout(exec);
	if (check_builtin(data, exec) == 1)
	{
		if (exec_builtin(data, exec) == 0)
			exit(0);
	}
	else if (exec->cmd_path)
	{
		if (execve(exec->cmd_path, exec->cmd_exec, data->env) == -1)
			perror("execve");
	}
	exit(1);
}

int	change_fdin(t_exec *exec)
{
	if (exec->fdin != STDIN_FILENO)
	{
		dup2(exec->fdin, STDIN_FILENO);
		if (close(exec->fdin) == -1)
			return (1);
	}
	return (0);
}

int	change_fdout(t_exec *exec)
{
	if (exec->fdout != STDOUT_FILENO)
	{
		dup2(exec->fdout, STDOUT_FILENO);
		if (close(exec->fdout) == -1)
			return (1);
	}
	return (0);
}
