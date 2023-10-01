/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/01 02:28:45 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//definit le fdin :
//					stdin
//					fichier
//					pipefd[0]
//					heredoc
int	exec_set_in(t_data *data, t_exec *exec)
{
	(void)data;
	if (exec->delimiter_nb)
	{
		heredoc(exec);
		exec->fdin = open(".heredoc", O_RDONLY);
		// ne marche pas parfaitement notamment :
		// tous les "heredoc>" sont a la fin au lieu d'etre en debut de ligne
	}
	else if (exec->in_nb == 1)
		exec->fdin = open(exec->in[0], O_RDONLY);
	else if (exec->id_exec == 0)
		exec->fdin = STDIN_FILENO;
	else if (exec->id_exec != 0)
	{
		if (data->exec[exec->id_exec - 1])
			exec->fdin = data->exec[exec->id_exec - 1]->fdin_next;
	}
	return (0);
}

//definit le fdout:
//					stdout
//					fichier
//					pipefd[1]
int	exec_set_out(t_data *data, t_exec *exec)
{
	if (exec->out_nb)
		exec->fdout = open(exec->out[0], O_RDONLY);
	else if (data->pipes_nb != 0)
	{
		exec->fdout = exec->pipefd[1];
		exec->fdin_next = exec->pipefd[0];
	}
	else
		exec->fdout = STDOUT_FILENO;
	return (0);
}

// definit les commandes
int	exec_set_cmd(t_data *data, t_exec *exec)
{
	int	len;
	int	index;

	len = 1 + exec->args_nb + exec->flags_nb;
	index = 0;
	exec->cmd_exec = malloc(sizeof(char *) * (len + 1));
	if (!exec->cmd_exec)
		return (1);
	while (index < len)
	{
		exec->cmd_exec[index] = data->command[index];
		index++;
	}
	exec->cmd_exec[index] = NULL;
	return (0);
}

// definit le path des commandes
int	exec_set_path(t_data *data, t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/'))
		exec->path_cmd = exec->cmd;
	else
	{
		exec->path_cmd = path_find_cmd(data, exec);
		if (!exec->path_cmd)
			return (1);
	}
	return (0);
}

// set les fdin et fdout de chaque commande
int	exec_set_exec(t_data *data, t_exec *exec)
{
	if (!check_builtin(data, exec))
	{
		if (exec_set_cmd(data, exec))
			return (perror("exec_set_cmd failed"), 1);
		if (exec_set_path(data, exec))
			return (perror("exec_set_path failed"), 1);
	}
	if (set_pipe(data, exec))
		return (perror("pipe_set failed"), 1);
	if (exec_set_in(data, exec))
		return (perror("exec_set_in failed"), 1);
	if (exec_set_out(data, exec))
		return (perror("exec_set_in failed"), 1);
	return (0);
}
