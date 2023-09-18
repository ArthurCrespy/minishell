/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:45:49 by acrespy           #+#    #+#             */
/*   Updated: 2023/06/14 10:45:49 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_processing(t_data *data)
{
	int	i;

	i = 0;
	while (data->command[i])
	{
		if (!ft_strcmp(data->command[i], "exit"))
			ft_exit(data, 0, NULL);
		i++;
	}
}
