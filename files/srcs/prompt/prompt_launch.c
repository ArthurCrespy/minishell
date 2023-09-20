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
		printf("lexing[%d] = %s\n", i, data->command[i]);
		i++;
	}
}

void    print_exec(t_data *data)
{
	int i;

	i = 0;
	while (data->exec[i])
	{
		printf("parsing[%d] | cmd   = %s\n", i, data->exec[i]->cmd);
		for (int j = 0; data->exec[i]->flags[j]; j++)
			printf("parsing[%d] | flags = %s\n", i, data->exec[i]->flags[j]);
		for (int j = 0; data->exec[i]->args[j]; j++)
			printf("parsing[%d] | args  = %s\n", i, data->exec[i]->args[j]);
		for (int j = 0; data->exec[i]->in[j]; j++)
			printf("parsing[%d] | in    = %s\n", i, data->exec[i]->in[j]);
		for (int j = 0; data->exec[i]->out[j]; j++)
			printf("parsing[%d] | out   = %s\n", i, data->exec[i]->out[j]);
		for (int j = 0; data->exec[i]->out_append[j]; j++)
			printf("parsing[%d] | oua   = %s\n", i, data->exec[i]->out_append[j]);
		for (int j = 0; data->exec[i]->delimiter[j]; j++)
			printf("parsing[%d] | del   = %s\n", i, data->exec[i]->delimiter[j]);
		i++;
	}
}

char	*prompt_welcome(t_data *data)
{
	char	*tmp;
	char	*path;
	char	*device;
	char	*result;

	path = ft_path(data);
	device = ft_device(data);
	result = ft_strjoin(env_return(data, "USER"), "@");
	tmp = ft_strjoin(result, device);
	free(result);
	result = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(result, path);
	free(result);
	result = ft_strjoin(tmp, "> ");
	free(tmp);
	free(path);
	free(device);
	return (result);
}

void	prompt_launch(t_data *data)
{
	char	*prompt;
	char	*input;

	data->history = NULL;
	signal_status(0, 1);
	while (1)
	{
		prompt = prompt_welcome(data);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (ft_strcmp(input, "") != 0)
		{
			history_add(data, input);
			command_parsing(data, input);
			key_processing(data, '\n');
			print_command(data);
			printf("-----------------------\n");
			print_exec(data);
			ft_free_tab(data->command);
		}
	}
}
