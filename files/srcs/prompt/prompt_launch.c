/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:36:34 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/19 13:36:34 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_command(t_data *data)
{
	int	i;

	i = 0;
	while (data->command[i])
	{
		printf("command[%d] = %s\n", i, data->command[i]);
		i++;
	}
}

void	prompt_launch(t_data *data)
{
	char	*input;

	data->history = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (ft_strcmp(input, "") != 0)
			history_add(data, input);
		command_parsing(data, input);
		key_processing(data, '\n');
		print_command(data);
		ft_free_tab(data->command);
	}
}
