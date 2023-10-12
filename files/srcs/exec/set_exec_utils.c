/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:23:27 by abinet            #+#    #+#             */
/*   Updated: 2023/10/12 13:15:50 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Define fdin if:
//  -> stdin
//  -> pipefd[0]
int	exec_set_in(t_data *data, t_exec *exec)
{
	if (exec->id_exec == 0)
		exec->fdin = STDIN_FILENO;
	else if (exec->id_exec != 0)
	{
		if (data->exec[exec->id_exec - 1])
			exec->fdin = data->exec[exec->id_exec - 1]->pipefd[0];
	}
	return (0);
}

// Define fdout:
//  -> stdout
//  -> pipefd[1]
int	exec_set_out(t_data *data, t_exec *exec)
{
	if (data->pipes_nb != 0)
		exec->fdout = exec->pipefd[1];
	else
		exec->fdout = STDOUT_FILENO;
	return (0);
}

// Define redir in:
//  -> filein
//  -> heredoc
int	if_redir_in(t_data *data, t_exec *exec, int index)
{
	if (exec->fdin != -1)
	{
		close(exec->fdin);
		exec->fdin = -1;
	}
	if (exec->id_exec > 0 && data->exec[exec->id_exec - 1]->pipefd[0] != -1)
	{
		close(data->exec[exec->id_exec - 1]->pipefd[0]);
		data->exec[exec->id_exec - 1]->pipefd[0] = -1;
	}
	if (exec->type[index] == REDIR_IN)
		exec->fdin = open(exec->content[index], O_RDWR, 644);
	if (exec->type[index] == DELIMITER)
	{
		if (heredoc(data, exec) == 1)
			return (exec->delimiter_num++, 1);
	}
	if (exec->fdin == -1)
		return (1);
	if (exec->fdin != -1 && (exec->cmd_path == NULL || exec->cmd == NULL))
	{
		close(exec->fdin);
		exec->fdin = -1;
	}
	return (0);
}

// Define fdout:
//  -> filout
//  -> append
int	if_redir_out(t_exec *exec, int index)
{
	int	type;

	type = exec->type[index];
	if (exec->fdout != -1)
	{
		close(exec->fdout);
		exec->fdout = -1;
	}
	if (type == REDIR_APPEND)
		exec->fdout = open(exec->content[index],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (type == REDIR_OUT)
		exec->fdout = open(exec->content[index],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->fdout == -1)
		return (1);
	if (exec->fdout != -1 && exec->cmd == NULL)
	{
		close(exec->fdout);
		exec->fdout = -1;
	}
	return (0);
}

// void	handle_open_error(void)
// {
// 	// if (errno == ENOENT)
// 	// 	perror(" ");
// 	// if (errno == EACCES)
// 	// 	perror(" ");
// 	// if (errno == EISDIR)
// }
