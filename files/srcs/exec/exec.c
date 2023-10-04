/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:35 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/04 12:06:20 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifie que le launch s'affiche bien
// boucle pour lancer chaque commande a la suite
int	exec_run(t_data *data)
{
	int		index;
	int	status;

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
			if (data->pipes_nb == 0 && index == 0
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
	while (wait(&status) != -1)
		continue ;
	// data->return_value = WEXITSTATUS(status);
	// printf("return value : %d\n", data->return_value);
	// printf("status : %d\n", status);
	return (0);
}
