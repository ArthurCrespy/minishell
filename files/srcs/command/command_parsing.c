/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 17:19:24 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_command_block(t_data *data, t_exec **exec, int *i, int *j)
{
	if (!data->command[(*i)])
	{
		data->exec_launch = false;
		return ;
	}
	exec[(*j)] = exec_new_node(data);
	if ((*i) > 0 && data->command[(*i)][0] == '|')
		(*i)++;
	exec[(*j)]->cmd = ft_strdup(*data, data->command[(*i)]);
	(*i)++;
	while (data->command[(*i)] && data->command[(*i)][0] == '-')
		exec[(*j)]->flags[exec[(*j)]->flags_nb++] = ft_strdup(*data,
				data->command[(*i)++]);
	while (data->command[(*i)] && data->command[(*i)][0] != '|')
	{
		parse_command_or_args(data, exec[(*j)], i);
		(*i)++;
	}
	exec[(*j)] = exec_old_node(exec[(*j)]);
	(*j)++;
}

t_exec	**node(t_data *data)
{
	int		i;
	int		j;
	t_exec	**exec;

	i = 0;
	j = 0;
	exec = (t_exec **)malloc(sizeof(t_exec *)
			* ft_tabcount(data->command, '|') + 100);
	if (!exec)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: node");
	while (data->command[i])
		process_command_block(data, exec, &i, &j);
	exec[j] = NULL;
	return (exec);
}

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
	data->exec = node(data);
	free(command);
}
