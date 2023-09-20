/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing_scratch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:10:31 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/19 15:10:31 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_print_exec(t_exec *exec)
{
	t_exec *tmp;

	tmp = exec;
	printf("+---------------------------------------------------------------------+\n");
	printf("| type |     cmd     | flags |     args     |   in   |   out   | pipe |\n");
	printf("+---------------------------------------------------------------------+\n");
	for (int i = 0; tmp; tmp = tmp->next, i++)
	{
		printf("|  %d  | %11s | %5s | %12s | %6s | %7s | %d |\n", tmp->type, tmp->cmd, tmp->flags, tmp->args, tmp->in, tmp->out[0], tmp->out_pipe);
		for (int j = 1; tmp->out[j]; i++)
			printf("+--------------------------------------------| %7s |------+\n", tmp->out[j]);
	}
}



int     ft_istoken(char *str)
{
	if (ft_strcmp(str, "&&") == 0)
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

void exec_add_node(t_exec *exec, t_exec *new)
{
	t_exec *tmp;

	if (!exec)
	{
		exec = new;
		exec->prev = NULL;
		exec->next = NULL;
	}
	else
	{
		tmp = exec;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

char *exec_parsing_input(t_data *data, t_exec *exec)
{
	(void)data;
	t_exec *tmp;

	tmp = exec;
	if (!tmp)
		return ("stdin");
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->out_pipe == 1)
			return ("pipe");
		else
			return (tmp->cmd);
	}
}

void exec_parsing_token(t_data *data, t_exec *exec, int *i)
{
	t_exec *new;

	new = (t_exec *)malloc(sizeof(t_exec));
	if (!new)
		ft_exit(data, 1, "malloc failed - ORIGIN: exec_parsing_token");
	new->flags = NULL;
	new->args = NULL;
	new->out = NULL;
	new->out_pipe = 0;
	new->in = exec_parsing_input(data, exec);

	new->type = ft_istoken(data->command[(*i)]);
	new->cmd = ft_strdup(*data, data->command[(*i)]);
	(*i)++;
	//ft_print_exec(new);
}

void exec_parsing_cmd(t_data *data, t_exec *exec, int *i)
{
    int j;
    t_exec *new;

	j = 0;
	new = (t_exec *)malloc(sizeof(t_exec));
    if (!new)
        ft_exit(data, 1, "malloc failed - ORIGIN: exec_parsing_cmd");

    new->out = NULL;
    new->out_pipe = 0;
    new->in = exec_parsing_input(data, exec);
    new->type = CMD;
    new->cmd = ft_strdup(*data, data->command[(*i)++]);

	while (data->command[(*i)])
	{
		//if ()
	}

    while (data->command[(*i)] && data->command[(*i)][0] == '-')
	{
        new->flags = ft_strjoin(new->flags, data->command[(*i)++]);
        new->flags = ft_strjoin(new->flags, " ");
    }

    while (data->command[(*i)] && !(ft_istoken(data->command[(*i)])))
	{
        new->args = ft_strjoin(new->args, data->command[(*i)++]);
        new->args = ft_strjoin(new->args, " ");
    }

    while (data->command[(*i)])
	{
	    if (ft_istoken(data->command[(*i)]) == REDIR_IN
			|| ft_istoken(data->command[(*i)]) == REDIR_APPEND)
		{
	        (*i)++;
	        new->out[j] = ft_strdup(*data, data->command[(*i)++]);
	        j++;

	        while (data->command[(*i)] && !(ft_istoken(data->command[(*i)])))
			{
	            new->args = ft_strjoin(new->args, data->command[(*i)++]);
	            new->args = ft_strjoin(new->args, " ");
	        }
	    }
		else if (ft_istoken(data->command[(*i)]) == PIPE)
		{
	        new->out_pipe = 1;
	        (*i)++;
	    }
		else
			break;
    }
    //  ft_print_exec(new);
    exec_add_node(exec, new);
}

t_exec  *exec_parsing(t_data *data)
{
	int     i;
	t_exec  *exec;

	i = 0;
	exec = NULL;
	if (!(ft_istoken(data->command[i])))
		exec_parsing_cmd(data, exec, &i);
	else if (ft_istoken(data->command[i]) == SEMICOLON
			|| ft_istoken(data->command[i]) == AND
			|| ft_istoken(data->command[i]) == OR)
		exec_parsing_token(data, exec, &i);
	//ft_print_exec(exec);
	return (exec);
}