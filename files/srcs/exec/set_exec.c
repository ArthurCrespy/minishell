/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:51:59 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//definit le fdin :
//					stdin
//					fichier
//					pipefd[0]
//					heredoc
int	exec_set_in(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (exec->delimiter_nb)
	{
		heredoc(exec);
		pipex->fdin = open(".heredoc", O_RDONLY);
		// ne marche pas parfaitement notamment :
		// tous les "heredoc>" sont a la fin au lieu d'etre en debut de ligne
	}
	else if (exec->in_nb == 1)
		pipex->fdin = open(exec->in[0], O_RDONLY);
	else if (exec->id_exec == 0)
		pipex->fdin = STDIN_FILENO;
	else
		pipex->fdin = data->exec[exec->id_exec - 1]->pipex->pipefd[0];
	return (0);
}

//definit le fdout:
//					stdout
//					fichier
//					pipefd[1]
int	exec_set_out(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (exec->out_nb)
		pipex->fdout = open(exec->out[0], O_RDONLY);
	else if (data->pipes_nb != 0)
		pipex->fdout = pipex->pipefd[1];
	else
		pipex->fdout = STDOUT_FILENO;
	return (0);
}

// definit les commandes
int	exec_set_cmd(t_data *data, t_exec *exec, t_pipex *pipex)
{
	int	len;
	int	index;

	len = 1 + exec->args_nb + exec->flags_nb;
	index = 0;
	pipex->cmd = malloc(sizeof(char *) * (len + 1));
	if (!pipex->cmd)
		return (1);
	while (index < len)
	{
		pipex->cmd[index] = data->command[index];
		index++;
	}
	pipex->cmd[index] = NULL;
	return (0);
}

// definit le path des commandes
int	exec_set_path(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (ft_strchr(exec->cmd, '/'))
		pipex->path_cmd = exec->cmd;
	else
	{
		pipex->path_cmd = path_find_cmd(data, exec, pipex);
		if (!pipex->path_cmd)
			return (perror("raté"), 1);
	}
	return (0);
}

// malloc la structure pipex qui possede les infos des redirections
// set les fdin et fdout de chaque commande
int	exec_set_exec(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (exec_set_cmd(data, exec, pipex))
		return (perror("raté"), 1);
	if (exec_set_path(data, exec, pipex))
		return (perror("raté"), 1);
	if (pipe_set(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_in(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_out(data, exec, pipex))
		return (perror("raté"), 1);
	return (0);
}
