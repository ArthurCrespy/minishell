/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/09/29 16:55:23 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fork puis donne les instructions pour les process enfants et parent
int	exec_launch(t_data *data, t_exec *exec, t_pipex * pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("raté"), 1);
	if (pid == 0) //&& data.path_cmd1)
	{
		exec_child(data, exec, pipex);
		//gestion erreur si exec mal passe
	}
	close(pipex->pipefd[1]);
	if (data->pipes_nb)
		data->pipes_nb--;
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
	(void)data;
	(void)exec;
	printf("fdin = %d\n", pipex->fdin);
	printf("fdout = %d\n", pipex->fdout);
	printf("pipefd[1] = %d\n", pipex->pipefd[1]);
	printf("pipefd[0] = %d\n", pipex->pipefd[0]);
	printf("nb_pipe = %d\n", data->pipes_nb);

	if (data->pipes_nb != 0)
	{
		dup2(pipex->fdout, STDOUT_FILENO);
		close(pipex->fdout);
	}

	if (data->pipes_nb == 0)
		close(pipex->pipefd[1]);

	dup2(pipex->fdin, STDIN_FILENO);
	close(pipex->fdin);

	if (data->pipes_nb != 0 && exec->id_exec == 0)
		close(pipex->pipefd[0]);

	if (exec_builtin(data, exec) == 1)
		execve(pipex->path_cmd, pipex->cmd, data->env);
	exit(0);
}
