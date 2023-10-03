/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/10/03 13:04:14 by abinet           ###   ########.fr       */
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
	//waitpid(pid, NULL, 0);
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
	// printf("id_exec = %d\n", exec->id_exec);
	// printf("cmd = %s\n", exec->cmd);
	// printf("path_cmd = %s\n", exec->path_cmd);
	// printf("nb_args child = %d\n", exec->args_nb);
	// printf("nb_flags = %d\n", exec->flags_nb);
	// int i;
	// i = 0;
	// while (exec->cmd_exec[i])
	// {
	// 	printf("cmd_exec = %s\n", exec->cmd_exec[i]);
	// 	i++;
	// }
	// pid_t pid = getpid();
	// printf("id_ exec = %d, pid = %d\n", exec->id_exec, pid);
	// printf("nb_pipe = %d\n", data->pipes_nb);
	// printf("fdin = %d\n", exec->fdin);
	// printf("fdout = %d\n", exec->fdout);
	// printf("pipefd[1] = %d\n", exec->pipefd[1]);
	// printf("on close pipefd[0] = %d\n", exec->pipefd[0]);
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
		execve(exec->path_cmd, exec->cmd_exec, data->env);
		perror("execve");
	}
	exit(1);
}

	// printf("id_exec = %d\n", exec->id_exec);
	// printf("fdin = %d\n", exec->fdin);
	// printf("fdout = %d\n", exec->fdout);
	// printf("pipefd[1] = %d\n", exec->pipefd[1]);
	// printf("pipefd[0] = %d\n", exec->pipefd[0]);
	// printf("nb_pipe = %d\n", data->pipes_nb);
	// printf("cmd = %s\n", exec->cmd);
	// printf("path_cmd = %s\n", exec->path_cmd);
	// printf("nb_args child = %d\n", exec->args_nb);
	// printf("nb_flags = %d\n", exec->flags_nb);
	// int i;
	// while (exec->cmd_exec[i])
	// {
	// 	printf("cmd_exec = %s\n", exec->cmd_exec[i]);
	// 	i++;
	// }
	// i = 0;
	// while (exec->args[i])
	// {
	// 	printf("args = %s\n", exec->args[i]);
	// 	i++;
	// }
	// i = 0;
	// while (exec->flags[i])
	// {
	// 	printf("flags = %s\n", exec->flags[i]);
	// 	i++;
	// }

	// printf("\n");
