/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/06 21:42:49 by abinet           ###   ########.fr       */
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
	while (data->exec[index])
	{
		data->exec[index]->id_exec = index;
		if (exec_set_all(data, data->exec[index]) == 0)
		{
			if (exec_set_ok(data, data->exec[index], index) == 1)
				return (1);
		}
		else
		{
			if (data->pipes_nb > 0)
			{
				data->pipes_nb--;
				close(data->exec[index]->pipefd[1]);
			}
			data->return_value = 1;
		}
		index++;
	}
	if (check_builtin(data, data->exec[0]) == 0 || index > 1)
		wait_all(data);
	if (data->exec[--index]->fdout == -1)
		data->return_value = 1;
	return (0);
}

int	exec_set_ok(t_data *data, t_exec *exec, int index)
{
	(void)exec;
	if (data->pipes_nb == 0 && index == 0 && data->exec[index]->out_nb == 0
		&& check_builtin(data, data->exec[index]) == 1)
	{
		if (exec_builtin(data, data->exec[index]) == 1)
			return (1);
	}
	else
	{
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
	while (data->exec[index])
	{
		waitpid(data->exec[index]->pid, &status, 0);
		signal_handle(data, 0);
		if (WIFEXITED(status))
			data->return_value = WEXITSTATUS(status);
		index++;
	}
	return (0);
}
