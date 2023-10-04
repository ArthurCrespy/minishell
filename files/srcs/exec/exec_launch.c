/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/10/04 19:00:01 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fork puis donne les instructions pour les process enfants et parent
int	exec_launch(t_data *data, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		exec_child(data, exec);
		perror("execve");
	}
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
	}
	else
		waitpid(pid, &data->return_value, 0);
	return (0);
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
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
			perror("close fdin child");
	}
	return (0);
}

int	change_fdout(t_exec *exec)
{
	if (exec->fdout != STDOUT_FILENO)
	{
		dup2(exec->fdout, STDOUT_FILENO);
		if (close(exec->fdout) == -1)
			perror("close fdout child");
	}
	return (0);
}
