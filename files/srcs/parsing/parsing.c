/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:24 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/26 20:52:28 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Parse the command and store it in data->exec
void	ft_exec_data_process(t_data *data, t_exec **exec, int *i, int *j)
{
	if (!data->command[(*i)])
	{
		data->exec_launch = false;
		return ;
	}
	exec[(*j)] = ft_exec_node_create(data);
	if ((*i) > 0 && data->command[(*i)][0] == '|')
	{
		data->pipes_nb++;
		(*i)++;
	}
	exec[(*j)]->cmd = ft_strdup(data, data->command[(*i)]);
	(*i)++;
	while (data->command[(*i)] && data->command[(*i)][0] == '-')
		exec[(*j)]->flags[exec[(*j)]->flags_nb++] = ft_strdup(data,
				data->command[(*i)++]);
	while (data->command[(*i)] && data->command[(*i)][0] != '|')
	{
		ft_exec_token_parser(data, exec[(*j)], i);
		(*i)++;
	}
	exec[(*j)] = ft_exec_node_null(exec[(*j)]);
	(*j)++;
}

// Prepare the data->exec array and launch the process
t_exec	**ft_exec_data_set(t_data *data)
{
	int		i;
	int		j;
	t_exec	**exec;

	i = 0;
	j = 0;
	exec = (t_exec **)malloc(sizeof(t_exec *)
			* (ft_tabcount(data->command, '|') + 2));
	if (!exec)
		ft_exit(data, -1, MALLOC_ERROR, "ft_exec_data_set");
	data->exec_launch = true;
	data->pipes_nb = 0;
	while (data->command[i])
		ft_exec_data_process(data, exec, &i, &j);
	exec[j] = NULL;
	return (exec);
}

// Parse the input command and store it in data->exec and in data->command
void	parsing_input(t_data *data, char *command)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	data->exec = NULL;
	data->exec_launch = false;
	parsing->command = ft_strdup(data, command);
	free(command);
	parsing->command = ft_char_replace(data, parsing, ' ');
	parsing->command = ft_char_replace(data, parsing, '\t');
	parsing->command = ft_char_replace(data, parsing, '\n');
	parsing->command = ft_char_replace(data, parsing, '\v');
	parsing->command = ft_operators_replace(data, parsing);
	if (!ft_quotes_closed(parsing->command))
	{
		free(parsing->command);
		free(parsing);
		return ;
	}
	parsing->command = ft_env_replace(data, parsing);
	parsing->command = ft_quotes_replace(data, parsing, '\"');
	parsing->command = ft_quotes_replace(data, parsing, '\'');
	data->command = ft_strsplit(data, parsing->command, '\x1F');
	data->exec = ft_exec_data_set(data);
	free(parsing->command);
	free(parsing);
}
