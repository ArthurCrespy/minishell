/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/25 21:34:24 by abinet           ###   ########.fr       */
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
	exec[(*j)]->cmd = ft_strdup(data, data->command[(*i)]);
	(*i)++;
	while (data->command[(*i)] && data->command[(*i)][0] == '-')
		exec[(*j)]->flags[exec[(*j)]->flags_nb++] = ft_strdup(data,
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
			* (ft_tablen(data->command) + 1));
	///// data->command c'est les commandes + les args + les flags
	//// donc ft_tablen ne renvoie pas le bon nombre de structure exec
	//// il faut une structure par commande et non pas une structure pour chaque commande, arg ou flag...
	if (!exec)
		ft_exit(data, -1, MALLOC_ERROR, "node");
	while (data->command[i])
		process_command_block(data, exec, &i, &j);
	exec[j] = NULL;
	return (exec);
}

void	command_parsing(t_data *data, char *command)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	data->exec_launch = false;
	parsing->command = ft_strdup(data, command);
	free(command);
	parsing->command = ft_char_replace(data, parsing, ' ');
	parsing->command = ft_char_replace(data, parsing, '\t');
	parsing->command = ft_char_replace(data, parsing, '\n');
	parsing->command = ft_char_replace(data, parsing, '\v');
	parsing->command = ft_operators_replace(data, parsing);
	if (!ft_quotes_closed(parsing->command))
		return ;
	parsing->command = ft_env_replace(data, parsing);
//	parsing->command = ft_quotes_replace(data, parsing, '\"');
//	parsing->command = ft_quotes_replace(data, parsing, '\'');
	data->command = ft_strsplit(data, parsing->command, '\x1F');
	data->exec_launch = true;
	data->exec = node(data);
	free(parsing->command);
	free(parsing);
}
