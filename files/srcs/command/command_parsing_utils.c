/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:15:48 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/21 16:15:48 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	*exec_new_node(t_data *data)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: exec_new_node");
	exec->cmd = NULL;
	exec->flags = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->args = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->in = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->out = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->out_append = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->delimiter = (char **)malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->flags_nb = 0;
	exec->args_nb = 0;
	exec->in_nb = 0;
	exec->out_nb = 0;
	exec->out_append_nb = 0;
	exec->delimiter_nb = 0;
	return (exec);
}

t_exec	*exec_old_node(t_exec *exec)
{
	exec->flags[exec->flags_nb] = NULL;
	exec->args[exec->args_nb] = NULL;
	exec->in[exec->in_nb] = NULL;
	exec->out[exec->out_nb] = NULL;
	exec->out_append[exec->out_append_nb] = NULL;
	exec->delimiter[exec->delimiter_nb] = NULL;
	return (exec);
}

void	parse_input_in_del(t_data *data, t_exec *exec, int *i)
{
	(*i)++;
	if (ft_istoken(data->command[(*i)]))
	{
		data->exec_launch = false;
		return ;
	}
	if (data->command[(*i) - 1][0] == '<' && data->command[(*i) - 1][1] == '<')
		exec->delimiter[exec->delimiter_nb++] = ft_strdup(*data,
				data->command[(*i)]);
	else
		exec->in[exec->in_nb++] = ft_strdup(*data, data->command[(*i)]);
}

void	parse_output_redirection(t_data *data, t_exec *exec, int *i)
{
	(*i)++;
	if (ft_istoken(data->command[*i]))
	{
		data->exec_launch = false;
		return ;
	}
	if (data->command[*i - 1][0] == '>' && data->command[*i - 1][1] == '>')
		exec->out_append[exec->out_append_nb++] = ft_strdup(*data,
				data->command[*i]);
	else
		exec->out[exec->out_nb++] = ft_strdup(*data, data->command[*i]);
}

void	parse_command_or_args(t_data *data, t_exec *exec, int *i)
{
	if (!data->command[(*i)])
		return ;
	if (data->command[(*i)] && data->command[(*i)][0] == '<')
		parse_input_in_del(data, exec, i);
	else if (data->command[(*i)] && data->command[(*i)][0] == '>')
		parse_output_redirection(data, exec, i);
	else if (data->command[(*i)] && data->command[(*i)][0] != '|')
		exec->args[exec->args_nb++] = ft_strdup(*data, data->command[(*i)]);
}
