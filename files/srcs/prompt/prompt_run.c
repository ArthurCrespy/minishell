/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:23:57 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/10 17:19:54 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Launch the prompt
void	prompt_run(t_data *data)
{
	char	*prompt;
	char	*input;

	data->history = NULL;
	while (1)
	{
		data->command = NULL;
		prompt = prompt_device_info(data);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "") != 0)
		{
			add_history(input);
			parsing_input(data, input);
			exec_run(data);
			ft_free_exec(data);
			ft_free_tab(data->command);
		}
	}
}
