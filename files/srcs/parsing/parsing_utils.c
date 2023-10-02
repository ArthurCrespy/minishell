/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:18 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 16:41:49 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Create a new node for exec
t_exec	*ft_exec_node_create(t_data *data)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		ft_exit(data, -1, MALLOC_ERROR, "ft_exec_node_create");
	exec->cmd = NULL;
	exec->flags = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->args = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->in = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->out = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->out_append = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->delimiter = malloc(sizeof(char *) * (ft_tabslen(data->command) + 1));
	exec->flags_nb = 0;
	exec->args_nb = 0;
	exec->in_nb = 0;
	exec->out_nb = 0;
	exec->out_append_nb = 0;
	exec->delimiter_nb = 0;
	exec->fdin = -1;
	exec->fdout = -1;
	exec->fdin_next = -1;
	exec->id_exec = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->cmd_exec = NULL;
	exec->path_cmd = NULL;
	return (exec);
}

// Set the exec elements to NULL
t_exec	*ft_exec_node_null(t_exec *exec)
{
	exec->flags[exec->flags_nb] = NULL;
	exec->args[exec->args_nb] = NULL;
	exec->in[exec->in_nb] = NULL;
	exec->out[exec->out_nb] = NULL;
	exec->out_append[exec->out_append_nb] = NULL;
	exec->delimiter[exec->delimiter_nb] = NULL;
	return (exec);
}

// Parse input tokens
void	ft_exec_token_input(t_data *data, t_exec *exec, int *i)
{
	(*i)++;
	if (ft_istoken(data->command[(*i)]))
	{
		data->exec_launch = false;
		return ;
	}
	if (data->command[(*i) - 1][0] == '<' && data->command[(*i) - 1][1] == '<')
		exec->delimiter[exec->delimiter_nb++] = ft_strdup(data,
				data->command[(*i)]);
	else
		exec->in[exec->in_nb++] = ft_strdup(data, data->command[(*i)]);
}

// Parse output tokens
void	ft_exec_token_output(t_data *data, t_exec *exec, int *i)
{
	(*i)++;
	if (ft_istoken(data->command[*i]))
	{
		data->exec_launch = false;
		return ;
	}
	if (data->command[*i - 1][0] == '>' && data->command[*i - 1][1] == '>')
		exec->out_append[exec->out_append_nb++] = ft_strdup(data,
				data->command[*i]);
	else
		exec->out[exec->out_nb++] = ft_strdup(data, data->command[*i]);
}

// Parse tokens
void	ft_exec_token_parser(t_data *data, t_exec *exec, int *i)
{
	if (!data->command[(*i)])
		return ;
	if (data->command[(*i)] && data->command[(*i)][0] == '<')
		ft_exec_token_input(data, exec, i);
	else if (data->command[(*i)] && data->command[(*i)][0] == '>')
		ft_exec_token_output(data, exec, i);
	else if (data->command[(*i)] && data->command[(*i)][0] != '|')
		exec->args[exec->args_nb++] = ft_strdup(data, data->command[(*i)]);
}
