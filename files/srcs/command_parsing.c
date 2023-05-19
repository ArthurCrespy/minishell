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

void	command_free(t_data *data)
{
	ft_free_tab(data->command);
}

void	command_parsing(t_data *data, char *command)
{
	data->command = ft_split(*data, command, ' ');
	command_free(data);
}
