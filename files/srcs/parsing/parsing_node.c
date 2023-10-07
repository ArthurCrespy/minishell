/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:15:01 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/02 10:15:01 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Set values for the new node
void	ft_exec_node_create2(t_exec *exec)
{
	exec->out_append_nb = 0;
	exec->delimiter_nb = 0;
	exec->fdin = -1;
	exec->fdout = -1;
	exec->fdin_next = -1;
	exec->id_exec = 0;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->cmd_exec = NULL;
	exec->cmd_path = NULL;
}

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
	exec->type = malloc(sizeof(int) * (ft_tabslen(data->command) + 1));
	exec->content = malloc(sizeof(int) * (ft_tabslen(data->command) + 1));
	exec->flags_nb = 0;
	exec->args_nb = 0;
	exec->in_nb = 0;
	exec->out_nb = 0;
	exec->ref_nb = 0;
	ft_exec_node_create2(exec);
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
