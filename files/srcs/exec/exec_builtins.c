/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:35:09 by abinet            #+#    #+#             */
/*   Updated: 2023/10/09 20:49:42 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// execute les builtins qui sont appeles
int	exec_builtin(t_data *data, t_exec *exec)
{
	if (exec_builtins_part1(data, exec) == 1)
		return (1);
	else if (exec_builtins_part2(data, exec) == 1)
		return (1);
	return (0);
}

int	exec_builtins_part1(t_data *data, t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
	{
		if (builtin_exit(data, data->exec[exec->id_exec]) == 1)
			return (1);
	}
	else if (!ft_strcmp(cmd, "pwd"))
	{
		if (builtin_pwd(data) == 1)
			return (1);
	}
	else if (!ft_strcmp(cmd, "cd"))
	{
		if (builtin_cd(data, data->exec[exec->id_exec]) == 1)
			return (1);
	}
	else if (!ft_strcmp(cmd, "unset"))
	{
		if (builtin_unset(data, data->exec[exec->id_exec]) == 1)
			return (1);
	}
	return (0);
}

int	exec_builtins_part2(t_data *data, t_exec *exec)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "echo"))
	{
		if (builtin_echo(data, data->exec[exec->id_exec]) == 1)
			return (1);
	}
	else if (!ft_strcmp(cmd, "export"))
	{
		if (builtin_export(data, data->exec[exec->id_exec]) == 1)
			return (1);
	}
	else if (!ft_strcmp(cmd, "env"))
	{
		if (builtin_env(data, false) == 1)
			return (1);
	}
	return (0);
}

int	check_builtin(t_data *data, t_exec *exec)
{
	char	*cmd;

	(void)data;
	cmd = exec->cmd;
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}
