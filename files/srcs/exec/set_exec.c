/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/04 18:56:54 by abinet           ###   ########.fr       */
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
	int	index;

	(void)data;
	index = 0;
	if (exec->delimiter_nb)
	{
		heredoc(exec);
		exec->fdin = open(".heredoc", O_RDONLY);
	}
	else if (exec->in_nb != 0)
	{
		while (index < exec->in_nb)
		{
			exec->fdin = open(exec->in[index], O_RDONLY);
			if (exec->fdin == -1)
				return (perror("open failed"), 1);
			if (index < exec->in_nb -1)
				close(exec->fdin);
			index++;
		}
	}
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
	int	index;

	if (exec->out_nb != 0)
	{
		index = 0;
		while (index < exec->out_nb)
		{
			exec->fdout = open(exec->out[index], O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (index < exec->out_nb -1)
				close(exec->fdout);
			index++;
		}
	}
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

	(void)data;
	len = 1 + exec->args_nb + exec->flags_nb;
	exec->cmd_exec = malloc(sizeof(char *) * (len + 1));
	if (!exec->cmd_exec)
		return (1);
	exec->cmd_exec[0] = exec->cmd;
	index = 0;
	while (exec->args[index])
	{
		exec->cmd_exec[index + 1] = exec->args[index];
		index++;
	}
	index = 0;
	while (exec->flags[index])
	{
		exec->cmd_exec[index + 1 + exec->args_nb] = exec->flags[index];
		index++;
	}
	exec->cmd_exec[len] = NULL;
	return (0);
}

// definit le path des commandes
int	exec_set_path(t_data *data, t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/'))
		exec->cmd_path = ft_strdup(data, exec->cmd);
	else
	{
		exec->cmd_path = path_find_cmd(data, exec);
		if (!exec->cmd_path)
			return (1);
	}
	return (0);
}

// set les fdin et fdout de chaque commande
int	exec_set_all(t_data *data, t_exec *exec)
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
		return (perror("exec_set_out failed"), 1);
	return (0);
}
