/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:59:38 by abinet            #+#    #+#             */
/*   Updated: 2023/10/01 02:56:55 by abinet           ###   ########.fr       */
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
	if ((pid == 0) && exec->path_cmd)
	{
		//verifier le path dans le child
		printf("go chiiiiild -> id_exec = %d\n", exec->id_exec);
		exec_child(data, exec);
		perror("execve");
	}
	if (data->pipes_nb != 0)
		close(exec->pipefd[1]);
	if (exec->id_exec != 0)
		close(data->exec[exec->id_exec - 1]->pipefd[0]);
	// if (exec->id_exec != 0)
	// {
	// 	if (close(exec->pipefd[0]) == -1)
	// 		perror("close pipefd[0] parent");
	// }
	// if (data->pipes_nb == 0)
	// {
	// 	if (close(exec->pipefd[1]) == -1)
	// 		perror("close pipefd[1] parent");
	// }
	if (data->pipes_nb)
		data->pipes_nb--;
	if (exec->delimiter_nb)
		unlink(".heredoc");
	if (check_builtin(data, exec) == 0)
	{
		free(exec->cmd_exec);
		free(exec->path_cmd);
	}
	// printf("id_exec = %d\n", exec->id_exec);
	// printf("fdin = %d\n", exec->fdin);
	// printf("fdout = %d\n", exec->fdout);
	// printf("pipefd[1] = %d\n", exec->pipefd[1]);
	// printf("pipefd[0] = %d\n", exec->pipefd[0]);
	// printf("nb_pipe = %d\n", data->pipes_nb);
	return (0);
}

// remplace les stdin et stdout par les fdin et fdout correspondants
// lance l'exec
void	exec_child(t_data *data, t_exec *exec)
{
	printf("id_exec = %d\n", exec->id_exec);
	printf("fdin = %d\n", exec->fdin);
	printf("fdout = %d\n", exec->fdout);
	printf("pipefd[1] = %d\n", exec->pipefd[1]);
	printf("pipefd[0] = %d\n", exec->pipefd[0]);
	printf("nb_pipe = %d\n", data->pipes_nb);
	if (exec->id_exec != 0)
	{
		close(exec->pipefd[1]);
		dup2(exec->fdin, STDIN_FILENO);
		if (close(exec->fdin) == -1)
			perror("close fdin child");
	}
	if (data->pipes_nb != 0)
	{
		close(exec->pipefd[0]);
		dup2(exec->fdout, STDOUT_FILENO);
		if (close(exec->fdout) == -1)
			perror("close fdout child");
	}
	char *fd;
	fd = ft_itoa(STDOUT_FILENO);
	ft_putstr_fd("\nstdout =", 4);
	ft_putstr_fd(fd, 4);
	ft_putstr_fd("\n", 4);
	if (exec_builtin(data, exec) == 1)
		execve(exec->path_cmd, exec->cmd_exec, data->env);
	exit(0);
}







// //fork puis donne les instructions pour les process enfants et parent
// int	exec_launch(t_data *data, t_exec *exec, t_exec * exec)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("raté"), 1);
// 	if (pid == 0) //&& data.path_cmd1)
// 	{
// 		exec_child(data, exec, exec);
// 		//gestion erreur si exec mal passe
// 	}
// 	// if (data->pipes_nb != 0 || exec->id_exec != 0)
// 	// {
// 	// 	if (close(exec->pipefd[1]) == -1)
// 	// 		perror("close pipefd[1] parent");
// 	// }
// 	if (data->pipes_nb)
// 		data->pipes_nb--;
// 	if (exec->delimiter_nb)
// 		unlink(".heredoc");
// 	if (check_builtin(data, exec) == 0)
// 	{
// 		free(exec->cmd);
// 		free(exec->path_cmd);
// 	}
// 	//free(exec);
// 	return (0);
// }

// // remplace les stdin et stdout par les fdin et fdout correspondants
// // lance l'exec
// void	exec_child(t_data *data, t_exec *exec, t_exec *exec)
// {
// 	(void)data;
// 	(void)exec;
// 	printf("fdin = %d\n", exec->fdin);
// 	printf("fdout = %d\n", exec->fdout);
// 	printf("pipefd[1] = %d\n", exec->pipefd[1]);
// 	printf("pipefd[0] = %d\n", exec->pipefd[0]);
// 	printf("nb_pipe = %d\n", data->pipes_nb);

// 	if (data->pipes_nb != 0)
// 	{
// 		dup2(exec->fdout, STDOUT_FILENO);
// 		if (close(exec->fdout) == -1)
// 			perror("close fdout child");
// 	}

// 	if (data->pipes_nb == 0 && exec->id_exec != 0)
// 	{
// 		if (close(exec->pipefd[1]) == -1)
// 			perror("close pipefd[1] child");
// 	}

// 	dup2(exec->fdin, STDIN_FILENO);
// 	if (close(exec->fdin) == -1)
// 			perror("close fdin child");

// 	if (data->pipes_nb != 0 && exec->id_exec == 0)
// 	{
// 		if (close(exec->pipefd[0]) == -1)
// 			perror("close pipefd[0] child");
// 	}
// 	if (exec_builtin(data, exec) == 1)
// 		execve(exec->path_cmd, exec->cmd, data->env);
// 	exit(0);
// }
