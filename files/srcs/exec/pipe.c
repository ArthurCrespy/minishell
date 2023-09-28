/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:54:17 by abinet            #+#    #+#             */
/*   Updated: 2023/09/28 17:11:21 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cree le nombre de pipes necessaires
int	set_pipe(t_data *data, t_exec *exec, t_pipex *pipex)
{
	(void)exec;
	(void)pipex;
	if (data->pipes_nb == 0)
		return (0);
	else
	{
		if (pipe(pipex->pipefd) == -1)
			return (1);
	}
	return (0);
}
