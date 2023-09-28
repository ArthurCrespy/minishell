/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/09/28 15:22:40 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fork puis donne les instructions pour les process enfants et parent
int	exec_launch(t_data *data, t_exec *exec, t_pipex * pipex)
{
	(void)exec;
	// pid_t	pid;

	// printf("foooork\n");
	// pid = fork();
	// if (pid == -1)
	// 	return (perror("raté"), 1);
	// if (pid == 0) //&& data.path_cmd1)
	// {
	// 	exec_child(data, exec, pipex);
	// 	//gestion erreur si exec mal passe
	// }
	if (data->pipes_nb)
	{
		close(pipex->pipefd[1]);
		data->pipes_nb--;
	}
	if (pipex->fdin != -1)
	{
		printf("on est la\n");
		close(pipex->fdin);
	}
	if (exec->delimiter_nb)
		unlink(".heredoc");
	//free(pipex->cmd);
	free(pipex);
	return (0);
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
void	exec_child(t_data *data, t_exec *exec, t_pipex *pipex)
{
	(void)pipex;
	(void)data;
	(void)exec;
	// if (exec_builtin(data, exec) == 1)
	// {
	// 	if (data->pipes_nb != 0)
	// 		close(pipex->pipefd[0]);
	// 	dup2(pipex->fdin, STDIN_FILENO);
	// 	close(pipex->fdin);
	// 	dup2(pipex->fdout, STDOUT_FILENO);
	// 	if (data->pipes_nb != 0)
	// 		close(pipex->pipefd[1]);
	// 	execve(pipex->path_cmd, pipex->cmd, data->env);
	// }
	if (exec_builtin(data, exec) == 1)
		execve(pipex->path_cmd, pipex->cmd, data->env);
	printf("end of child\n");
	exit(0);
}
