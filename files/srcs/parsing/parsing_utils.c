/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:52:18 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/05 20:43:52 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{
		exec->delimiter[exec->delimiter_nb++] = ft_strdup(data,
				data->command[(*i)]);
		exec->type[exec->ref_nb] = DELIMITER;
		exec->content[exec->ref_nb++] = ft_strdup(data, data->command[(*i)]);
	}
	else
	{
		exec->in[exec->in_nb++] = ft_strdup(data, data->command[(*i)]);
		exec->type[exec->ref_nb] = REDIR_IN;
		exec->content[exec->ref_nb++] = ft_strdup(data, data->command[(*i)]);
	}
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
	{
		exec->out_append[exec->out_append_nb++] = ft_strdup(data,
				data->command[*i]);
		exec->type[exec->ref_nb] = REDIR_APPEND;
		exec->content[exec->ref_nb++] = ft_strdup(data, data->command[*i]);
	}
	else
	{
		exec->out[exec->out_nb++] = ft_strdup(data, data->command[*i]);
		exec->type[exec->ref_nb] = REDIR_OUT;
		exec->content[exec->ref_nb++] = ft_strdup(data, data->command[*i]);
	}
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
	(*i)++;
}
