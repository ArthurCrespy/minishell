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

int	ft_istoken(char *str)
{
	if (!ft_strcmp(str, "&&"))
		return (AND);
	else if (!ft_strcmp(str, "||"))
		return (OR);
	else if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	else if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	else if (!ft_strcmp(str, ">>"))
		return (REDIR_APPEND);
	else if (!ft_strcmp(str, "<<"))
		return (DELIMITER);
	else
		return (0);
}

t_exec	*exec_new_node(t_data *data)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec) + 1);
	if (!exec)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: exec_new_node");
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
	if (!exec->cmd)
		exec->cmd = NULL;
	if (!exec->flags_nb)
		exec->flags = NULL;
	if (!exec->args_nb)
		exec->args = NULL;
	if (!exec->in_nb)
		exec->in = NULL;
	if (!exec->out_nb)
		exec->out = NULL;
	if (!exec->out_append_nb)
		exec->out_append = NULL;
	if (!exec->delimiter_nb)
		exec->delimiter = NULL;
	return (exec);
}


t_exec 	**node(t_data *data)
{
	int		i;
	int 	j;
	t_exec 	**exec;

	i = 0;
	j = 0;
	exec = (t_exec **)malloc(sizeof(t_exec *) * ft_tabcount(data->command, '|') + 100);
	if (!exec)
		ft_exit(data, MALLOC_ERROR, "malloc failed - ORIGIN: node");
	while (data->command[i])
	{
		exec[j] = exec_new_node(data);
		if (i > 0 && data->command[i][0] == '|')
			i++;
		exec[j]->cmd = ft_strdup(*data, data->command[i]);
		i++;
		while (data->command[i] && data->command[i][0] == '-')
			exec[j]->flags[exec[j]->flags_nb++] = ft_strdup(*data, data->command[i++]);
		while (data->command[i] && data->command[i][0] != '|')
		{
			if (data->command[i] && data->command[i][0] == '<')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					exec[j]->in[exec[j]->in_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '>')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					exec[j]->out[exec[j]->out_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '>' && data->command[i][1] == '>')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					exec[j]->out_append[exec[j]->out_append_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '<' && data->command[i][1] == '<')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					exec[j]->delimiter[exec[j]->delimiter_nb++] = ft_strdup(*data, data->command[i]);
			}
			else if (data->command[i] && data->command[i][0] != '|')
				exec[j]->args[exec[j]->args_nb++] = ft_strdup(*data, data->command[i]);
			i++;
		}
		exec[j] = exec_old_node(exec[j]);
		j++;
	}
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
