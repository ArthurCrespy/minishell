/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:23:27 by abinet            #+#    #+#             */
/*   Updated: 2023/10/07 17:08:29 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Define the fdin
//  -> stdin
//  -> file
//  -> pipefd[0]
//  -> heredoc
int	exec_set_in(t_data *data, t_exec *exec)
{
	if (exec->in_nb != 0)
	{
		if (if_redir_in(exec) == 1)
			return (1);
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

// Define the fdout
//  -> stdout
//  -> file
//  -> pipefd[1]
int	exec_set_out(t_data *data, t_exec *exec)
{
	if (exec->out_nb != 0 || exec->out_append_nb != 0)
	{
		if (if_redir_out(exec) == 1)
			return (1);
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

int	if_redir_in(t_exec *exec)
{
	int	index;

	index = 0;
	while (index < exec->in_nb)
	{
		if (!ft_strcmp(exec->in[index], "here_doc"))
				exec->fdin = heredoc(exec);
		else
			exec->fdin = open(exec->in[index], O_RDWR, 644);
		if (exec->fdin == -1)
			return (1);
		if (index < exec->in_nb -1)
			close(exec->fdin);
		index++;
	}
	return (0);
}

int	if_redir_out(t_exec *exec)
{
	int	index;
	int	out_nb;
	int	out_append_nb;

	out_nb = exec->out_nb;
	out_append_nb = exec->out_append_nb;
	index = 0;
	while (out_nb + out_append_nb > 0)
	{
		if (out_append_nb)
		{
			exec->fdout = open(exec->out_append[index],
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (exec->fdout == -1)
				return (1);
			out_append_nb--;
		}
		if (out_nb)
		{
			exec->fdout = open(exec->out[index],
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (exec->fdout == -1)
				return (1);
			out_nb--;
		}
		if ((out_append_nb + out_nb) > 1)
			close(exec->fdout);
		index++;
	}
	return (0);
}

void	handle_open_error(void)
{
	// if (errno == ENOENT)
	// 	perror(" ");
	// if (errno == EACCES)
	// 	perror(" ");
	// if (errno == EISDIR)
}
