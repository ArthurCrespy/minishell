/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:23:57 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 18:23:57 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_run(t_data *data)
{
	char	*prompt;
	char	*input;

	signal_status(0, 1);
	while (1)
	{
		prompt = prompt_device_info(data);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "") != 0)
		{
			data->command = NULL;
			add_history(input);
			parsing_input(data, input);
			exec_run(data);
			ft_free_exec(data);
			ft_free_tab(data->command);
		}
	}
}
