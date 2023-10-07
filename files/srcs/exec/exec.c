/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/04 18:40:05 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Launch the exec
// Loop to launch each command in a row
int	exec_run(t_data *data)
{
	int		index;
	int		status;

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
			if (data->pipes_nb == 0 && index == 0
				&& data->exec[index]->out_nb == 0
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
		}
		index++;
	}
	if (index > 1)
	{
		while (wait(&status) != -1)
			continue ;
		data->return_value = WEXITSTATUS(status);
	}
	return (0);
}
