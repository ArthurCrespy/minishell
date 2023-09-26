/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:54:17 by abinet            #+#    #+#             */
/*   Updated: 2023/09/26 16:56:08 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cree le nombre de pipes necessaires
int	pipe_set(t_data *data, t_exec *exec, t_pipex *pipex)
{
	int	index;

	(void)exec;
	(void)pipex;
	if (data->pipes_nb == 0)
		return (0);
	else
	{
		index = 0;
		while (index < data->pipes_nb)
		{
			if (pipe(data->exec[index]->pipex->pipefd) == -1)
				return (1);
			index++;
		}
	}
	return (0);
}
