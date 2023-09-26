/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:40:47 by abinet            #+#    #+#             */
/*   Updated: 2023/09/26 17:20:49 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// malloc la structure pipex qui possede les infos des redirections
// set les fdin et fdout de chaque commande
int	set_exec(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (set_cmd(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_path_cmd(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_pipe(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_in(data, exec, pipex))
		return (perror("raté"), 1);
	if (set_out(data, exec, pipex))
		return (perror("raté"), 1);
	return (0);
}

//definit le fdin :
//					stdin
//					fichier
//					pipefd[0]
//					here_doc
int	set_in(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (exec->delimiter_nb)
	{
		here_doc(exec);
		pipex->fdin = open(".here_doc", O_RDONLY);
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
int	set_out(t_data *data, t_exec *exec, t_pipex *pipex)
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
int	set_cmd(t_data *data, t_exec *exec, t_pipex *pipex)
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
int	set_path_cmd(t_data *data, t_exec *exec, t_pipex *pipex)
{
	if (ft_strchr(exec->cmd, '/'))
		pipex->path_cmd = exec->cmd;
	else
	{
		pipex->path_cmd = find_path_cmd(data, exec, pipex);
		if (!pipex->path_cmd)
			return (perror("raté"), 1);
	}
	return (0);
}
