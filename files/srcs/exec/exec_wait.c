/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:46:56 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/12 11:46:56 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_all(t_data *data)
{
	int		status;
	int		index;

	index = 0;
	status = 0;
	while (data->exec[index])
	{
		if (data->exec[index]->is_pid == true)
			waitpid(data->exec[index]->pid, &status, 0);
		if (g_status > 0)
			data->return_value = g_status;
		else if (data->exec[index]->is_pid == true && WEXITSTATUS(status))
			data->return_value = WEXITSTATUS(status);
		else if (data->exec[index]->is_pid == true && data->return_value != 1
			&& WIFEXITED(status))
			data->return_value = 0;
		signal_handle(data, 0);
		index++;
	}
	return (0);
}
