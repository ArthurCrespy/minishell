/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/04 17:20:34 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
int	exec_run(t_data *data)
{
	int		index;
	int		status;

	if (data->exec_launch == false)
	{
		printf("minishell: parse error\n");
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
