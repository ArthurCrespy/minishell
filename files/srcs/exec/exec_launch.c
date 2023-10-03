/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/10/03 17:23:14 by abinet           ###   ########.fr       */
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
		free(exec->path_cmd);
	}
	return (0);
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
void	exec_child(t_data *data, t_exec *exec)
{
	if (exec->fdin != STDIN_FILENO)
	{
		dup2(exec->fdin, STDIN_FILENO);
		if (close(exec->fdin) == -1)
			perror("close fdin child");
	}
	if (data->pipes_nb != 0)
	{
		close(exec->pipefd[0]);
	}
	if (exec->fdout != STDOUT_FILENO)
	{
		dup2(exec->fdout, STDOUT_FILENO);
		if (close(exec->fdout) == -1)
			perror("close fdout child");
	}
	if (check_builtin(data, exec) == 1)
	{
		if (exec_builtin(data, exec) == 0)
			exit(0);
	}
	else if (exec->path_cmd)
	{
		if (execve(exec->path_cmd, exec->cmd_exec, data->env) == -1)
			perror("execve");
	}
	exit(1);
}
