/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:36:34 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 22:51:48 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_command(t_data *data)
{
	int	i;

	i = 0;
	while (data->command[i])
	{
		printf("%s * ", data->command[i]);
		i++;
	}
	printf("\n");
}

void	print_exec(t_data *data)
{
	int i;

	i = 0;
	while (data->exec[i])
	{
		if (data->exec[i]->cmd)
			printf("cmd: %s * ",data->exec[i]->cmd);
		if (data->exec[i]->flags)
		{
			for (int j = 0; data->exec[i]->flags[j]; j++)
				printf("%s ", data->exec[i]->flags[j]);
			printf("* ");
		}
		if (data->exec[i]->args)
		{
			for (int j = 0; data->exec[i]->args[j]; j++)
				printf("%s ", data->exec[i]->args[j]);
			printf("* ");
		}
		if (data->exec[i]->in)
		{
			for (int j = 0; data->exec[i]->in[j]; j++)
				printf("%s ", data->exec[i]->in[j]);
			printf("* ");
		}
		if (data->exec[i]->out)
		{
			for (int j = 0; data->exec[i]->out[j]; j++)
				printf("%s ", data->exec[i]->out[j]);
			printf("* ");
		}
		if (data->exec[i]->out_append)
		{
			for (int j = 0; data->exec[i]->out_append[j]; j++)
				printf("%s ", data->exec[i]->out_append[j]);
			printf("* ");
		}
		if (data->exec[i]->delimiter)
		{
			for (int j = 0; data->exec[i]->delimiter[j]; j++)
				printf("%s ", data->exec[i]->delimiter[j]);
			printf("* ");
		}
		printf("\n");
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

void ft_free_exec(t_exec **exec)
{
	int i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->cmd)
			free(exec[i]->cmd);
		if (exec[i]->flags)
			ft_free_tab(exec[i]->flags);
		if (exec[i]->args)
			ft_free_tab(exec[i]->args);
		if (exec[i]->in)
			ft_free_tab(exec[i]->in);
		if (exec[i]->out)
			ft_free_tab(exec[i]->out);
		if (exec[i]->out_append)
			ft_free_tab(exec[i]->out_append);
		if (exec[i]->delimiter)
			ft_free_tab(exec[i]->delimiter);
		free(exec[i]);
		printf("free exec[%d]\n", i);
		i++;
	}
	free(exec);
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
			//exec(data);
			key_processing(data, '\n');
			print_command(data);
			printf("-----------------------\n");
			print_exec(data);
			ft_free_tab(data->command);
			ft_free_exec(data->exec);
		}
	}
}
