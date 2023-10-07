/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:51:54 by acrespy           #+#    #+#             */
/*   Updated: 2023/10/07 17:51:41 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Define the command to execute
int	exec_set_cmd(t_data *data, t_exec *exec)
{
	int	len;
	int	index;

	(void)data;
	len = 1 + exec->args_nb + exec->flags_nb;
	exec->cmd_exec = malloc(sizeof(char *) * (len + 1));
	if (!exec->cmd_exec)
		return (1);
	exec->cmd_exec[0] = exec->cmd;
	index = 0;
	while (exec->args[index])
	{
		exec->cmd_exec[index + 1] = exec->args[index];
		index++;
	}
	index = 0;
	while (exec->flags[index])
	{
		exec->cmd_exec[index + 1 + exec->args_nb] = exec->flags[index];
		index++;
	}
	exec->cmd_exec[len] = NULL;
	return (0);
}

// Define the path of the command
int	exec_set_path(t_data *data, t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/'))
		exec->cmd_path = ft_strdup(data, exec->cmd);
	else
	{
		exec->cmd_path = path_find_cmd(data, exec);
		if (!exec->cmd_path)
			return (1);
	}
	return (0);
}

// cree le nombre de pipes necessaires
int	set_pipe(t_data *data, t_exec *exec)
{
	if (data->pipes_nb == 0)
		return (0);
	else
	{
		if (pipe(exec->pipefd) == -1)
			return (1);
	}
	return (0);
}

// int	set_in_and_out(t_data *data, t_exec *exec)
// {
// 	int	index;
// 	int	type;

// 	index = 0;
// 	while (index < exec->ref_nb)
// 	{
// 		type = exec->content[index];
// 		if (type == REDIR_IN || type == DELIMITER)
// 		{
// 			if (if_redir_in(exec))
// 				return (1);
// 		}
// 		if (type == REDIR_OUT || type == REDIR_APPEND)
// 		{
// 			if (if_redir_out(exec))
// 				return (1);
// 		}
// 	}
// 	if (!exec->in_nb && exec->id_exec == 0)
// 		exec->fdin = STDIN_FILENO;
// }

// Catch the cmd and his path then set the fdin, fdout and pipefd
int	exec_set_all(t_data *data, t_exec *exec)
{
	int	return_value;

	return_value = 0;
	if (!check_builtin(data, exec))
	{
		if (exec_set_cmd(data, exec))
			return (ft_putstr_fd(exec->cmd, 2), perror(" "), 1);
		if (exec_set_path(data, exec))
			return (ft_putstr_fd(exec->cmd, 2), perror(" "), 1);
	}
	if (set_pipe(data, exec))
		return (perror("pipe_set failed"), 1);
	if (exec_set_in(data, exec))
	{
		ft_putstr_fd(exec->in[0], 2);
		perror(" ");
		return_value = 1;
	}
	if (exec_set_out(data, exec))
	{
		ft_putstr_fd(exec->out[0], 2);
		perror(" ");
		return_value = 1;
	}
	return (return_value);
}
