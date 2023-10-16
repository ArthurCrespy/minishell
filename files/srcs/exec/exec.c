/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/12 17:21:36 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Launch the exec
// Loop to launch each command in a row
int	exec_run(t_data *data)
{
	int		index;

	if (data->exec_launch == false)
	{
		ft_putstr_fd("minishell: parse error\n", 2);
		return (1);
	}
	index = 0;
	g_status = -1;
	while (data->exec[index])
	{
		data->return_value = 0;
		data->exec[index]->id_exec = index;
		if (exec_set_all(data, data->exec[index]) == 0)
		{
			if (exec_set_ok(data, data->exec[index], index) == 1)
				return (1);
		}
		else
			exec_set_ko(data, data->exec[index]);
		index++;
	}
	if (index > 0)
		wait_all(data);
	return (0);
}

void	ft_exec_close(t_data *data, t_exec *exec)
{
	data->pipes_nb--;
	if (exec->pipefd[1] != -1)
	{
		close(exec->pipefd[1]);
		exec->pipefd[1] = -1;
	}
	if (exec->pipefd[0] != -1 && exec->cmd_path == NULL)
	{
		close(exec->pipefd[0]);
		exec->pipefd[0] = -1;
	}
}

int	exec_set_ko(t_data *data, t_exec *exec)
{
	if (data->pipes_nb > 0)
		ft_exec_close(data, exec);
	if (exec->fdin != -1 && exec->id_exec > 0
		&& data->exec[exec->id_exec - 1]->cmd_path == NULL)
	{
		close(exec->fdin);
		exec->fdin = -1;
	}
	if (exec->cmd == NULL)
	{
		if (exec->fdout != -1)
		{
			close(exec->fdout);
			exec->fdout = -1;
		}
	}
	if (exec->cmd_path)
		free(exec->cmd_path);
	if (exec->cmd_exec)
		free(exec->cmd_exec);
	if (g_status > 0)
		data->return_value = g_status;
	else if (data->return_value == 0)
		data->return_value = 1;
	return (0);
}

void	ft_exec_delimiter(t_data *data, t_exec *exec)
{
	if (data->pipes_nb && exec->pipefd[1] != -1
		&& (exec->fdout != exec->pipefd[1]))
	{
		close(exec->pipefd[1]);
		exec->pipefd[1] = -1;
	}
	if (exec->delimiter_nb)
		unlink(".heredoc");
}

int	exec_set_ok(t_data *data, t_exec *exec, int index)
{
	if (exec->cmd == NULL && exec->id_exec != 0)
	{
		close(data->exec[exec->id_exec -1]->pipefd[0]);
		data->exec[exec->id_exec -1]->pipefd[0] = -1;
	}
	if (data->pipes_nb == 0 && index == 0 && data->exec[index]->ref_nb == 0
		&& check_builtin(data, data->exec[index]) == 1)
	{
		if (exec_builtin(data, data->exec[index]) == 1)
			return (1);
	}
	else
	{
		if (exec->cmd == NULL)
			ft_exec_delimiter(data, exec);
		else if (exec_launch(data, data->exec[index]) == 1)
			return (1);
		data->pipes_nb--;
	}
	return (0);
}
