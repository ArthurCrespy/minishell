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

#include "../../includes/minishell.h"

void	command_parsing(t_data *data, char *command)
{
	command = ft_char_replace(data, command, ' ');
	command = ft_char_replace(data, command, '\t');
	command = ft_char_replace(data, command, '\n');
	command = ft_char_replace(data, command, '\v');
	command = ft_operators_replace(data, command);
	command = ft_quotes_replace(data, command, '\"');
	command = ft_env_replace(data, command);
	command = ft_quotes_replace(data, command, '\'');
	data->command = ft_strsplit(*data, command, '\x1F');
	free(command);
}