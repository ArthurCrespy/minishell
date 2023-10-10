/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/10 01:20:40 by abinet           ###   ########.fr       */
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
	if (index > 0 && data->exec[index - 1]->is_pid == true)
		wait_all(data);
	return (0);
}

int	exec_set_ko(t_data *data, t_exec *exec)
{
	if (data->pipes_nb > 0)
	{
		data->pipes_nb--;
		close(exec->pipefd[1]);
	}
	if (data->return_value == 0)
		data->return_value = 1;
	return (0);
}

int	exec_set_ok(t_data *data, t_exec *exec, int index)
{
	(void)exec;
	if (data->pipes_nb == 0 && index == 0 && data->exec[index]->ref_nb == 0
		&& check_builtin(data, data->exec[index]) == 1)
	{
		if (exec_builtin(data, data->exec[index]) == 1)
			return (1);
	}
	else
	{
		if (data->pipes_nb && exec->fdout != exec->pipefd[1])
			close(exec->pipefd[1]);
		if (exec->cmd == NULL)
		{
			if (exec->delimiter_nb)
				unlink(".heredoc");
			return (0);
		}
		if (exec_launch(data, data->exec[index]) == 1)
			return (1);
	}
	return (0);
}

int	wait_all(t_data *data)
{
	int		status;
	int		index;

	index = 0;
	status = 0;
	while (data->exec[index])
	{
		waitpid(data->exec[index]->pid, &status, 0);
		if (g_status > 0)
			data->return_value = g_status;
		else if (WEXITSTATUS(status))
			data->return_value = WEXITSTATUS(status);
		else if (WIFEXITED(status))
			data->return_value = 0;
		signal_handle(data, 0);
		index++;
	}
	return (0);
}
