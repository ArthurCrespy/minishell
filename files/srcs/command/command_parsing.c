/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:16 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 21:28:25 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    printt_exec(t_data *data, t_exec *tmp)
{
	(void)data;
	int i;

	i = 0;
	if (tmp)
	{
		printf("parsing[%d] | cmd   = %s\n", i, tmp->cmd);
		for (int j = 0; tmp->flags[j]; j++)
			printf("parsing[%d] | flags = %s\n", i, tmp->flags[j]);
		for (int j = 0; tmp->args[j]; j++)
			printf("parsing[%d] | args  = %s\n", i, tmp->args[j]);
		for (int j = 0; tmp->in[j]; j++)
			printf("parsing[%d] | in    = %s\n", i, tmp->in[j]);
		for (int j = 0; tmp->out[j]; j++)
			printf("parsing[%d] | out   = %s\n", i, tmp->out[j]);
		for (int j = 0; tmp->out_append[j]; j++)
			printf("parsing[%d] | oua   = %s\n", i, tmp->out_append[j]);
		for (int j = 0; tmp->delimiter[j]; j++)
			printf("parsing[%d] | del   = %s\n", i, tmp->delimiter[j]);
	}
}

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

t_exec	*new_node(t_data *data)
{
	t_exec	*tmp;

	tmp = malloc(sizeof(t_exec));
	tmp->flags = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->args = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->in = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->out = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->out_append = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->delimiter = malloc(sizeof(char *) * ft_tablen(data->command));
	tmp->cmd = NULL;
	tmp->flags[0] = NULL;
	tmp->args[0] = NULL;
	tmp->in[0] = NULL;
	tmp->out[0] = NULL;
	tmp->out_append[0] = NULL;
	tmp->delimiter[0] = NULL;
	tmp->flags_nb = 0;
	tmp->args_nb = 0;
	tmp->in_nb = 0;
	tmp->out_nb = 0;
	tmp->out_append_nb = 0;
	tmp->delimiter_nb = 0;
	return (tmp);
}


t_exec 	**node(t_data *data)
{
	int		i;
	int 	j;
	t_exec	*tmp;
	t_exec	**exec;

	i = 0;
	j = 0;
	exec = (t_exec **)malloc(sizeof(t_exec *) * ft_tabcount(data->command, '|') + 1);
	while (data->command[i])
	{
		tmp = new_node(data);
		tmp->cmd = ft_strdup(*data, data->command[i]);
		i++;
		while (data->command[i] && data->command[i][0] == '-')
				tmp->flags[tmp->flags_nb++] = ft_strdup(*data, data->command[i++]);

		while (data->command[i])
		{
			if (data->command[i] && data->command[i][0] == '<')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					tmp->in[tmp->in_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '>')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					tmp->out[tmp->out_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '>' && data->command[i][1] == '>')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					tmp->out_append[tmp->out_append_nb++] = ft_strdup(*data, data->command[i]);
			}

			else if (data->command[i] && data->command[i][0] == '<' && data->command[i][1] == '<')
			{
				i++;
				if (ft_istoken(data->command[i]))
					printf("error\n");
				else
					tmp->delimiter[tmp->delimiter_nb++] = ft_strdup(*data, data->command[i]);
			}
			else if (data->command[i] && data->command[i][0] != '|')
				tmp->args[tmp->args_nb++] = ft_strdup(*data, data->command[i]);

			if (data->command[i] && data->command[i][0] == '|')
			{
				exec[j] = tmp;
				j++;
				printt_exec(data, tmp);
				free(tmp);
				break ;
			}
			i++;
		}
	}
	// exec[j] = tmp;
	// j++;
	// exec[j] = NULL;
	// free(tmp);
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
