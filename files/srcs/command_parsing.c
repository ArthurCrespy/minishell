/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 17:24:24 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_parsing(t_data *data, char *command)
{
	int	i;

	i = 0;
	command = ft_replace_char(data, command, ' ');
	command = ft_replace_char(data, command, '\t');
	command = ft_replace_char(data, command, '\n');
	command = ft_replace_char(data, command, '\v');
	command = ft_replace_operators(data, command);
	data->command = ft_split(*data, command, '\x1F');
	free(command);
	while (data->command[i])
	{
		printf("command[%d] = %s\n", i, data->command[i]);
		i++;
	}
}
