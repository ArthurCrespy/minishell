/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/05 20:57:30 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
int	exec_run(t_data *data)
{
	int		index;
	//int		status;

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
	wait_all(data);
	if (data->exec[--index]->fdout == -1)
		data->return_value = 1;
	return (0);
}

int	wait_all(t_data *data)
{
	int		status;
	int		index;

	index = 0;
	while (data->exec[index])
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			data->return_value = WEXITSTATUS(status);
		index++;
	}
	return (0);
}

	// if (index > 1)
	// {
	// 	while (wait(&status) != -1)
	// 		continue ;
	// 	if (WIFEXITED(status))
	// 		data->return_value = WEXITSTATUS(status);
	// }
	// else
	// 	waitpid(-1, &status, 0);
